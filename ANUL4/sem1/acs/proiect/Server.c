// Server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include "Protocol.h"

typedef struct {
    int fd;
    char username[64];
    int joined;
} client_t;

static client_t clients[MAX_CLIENTS];

// read exactly len bytes
static int read_n(int fd, void *buf, uint32_t len) {
    char *p = (char*)buf;
    uint32_t left = len;
    while (left > 0) {
        ssize_t r = recv(fd, p, left, 0);
        if (r <= 0) return r;
        p += r; left -= r;
    }
    return len;
}

// send framed message to client
static int send_message_fd(int fd, uint8_t op, const void *payload, uint32_t payload_len) {
    uint32_t total_len = 1 + payload_len;
    uint32_t be_len = htonl(total_len);
    if (send(fd, &be_len, sizeof(be_len), 0) != sizeof(be_len)) return -1;
    if (send(fd, &op, 1, 0) != 1) return -1;

    if (payload_len > 0 && payload) {
        const char *p = (const char*)payload;
        uint32_t left = payload_len;
        while (left > 0) {
            ssize_t s = send(fd, p, left, 0);
            if (s <= 0) return -1;
            p += s; left -= s;
        }
    }
    return 0;
}

// save content to disk
static int save_document_to_disk(const char *filename, const char *data) {
    FILE *f = fopen(filename, "wb");
    if (!f) return -1;
    if (data) fwrite(data, 1, strlen(data), f);
    fclose(f);
    return 0;
}

// load file content from disk
static char *load_file_content(const char *filename, size_t *out_len) {
    if (!filename) return NULL;
    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);
    char *buf = malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t got = fread(buf, 1, (size_t)sz, f);
    buf[got] = '\0';
    fclose(f);
    if (out_len) *out_len = got;
    return buf;
}

// add client
static int add_client(int fd) {
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].fd == 0) {
            clients[i].fd = fd;
            clients[i].username[0] = '\0';
            clients[i].joined = 0;
            return i;
        }
    }
    return -1;
}

static void remove_client_index(int idx) {
    if (clients[idx].fd) {
        close(clients[idx].fd);
        clients[idx].fd = 0;
        clients[idx].username[0] = '\0';
        clients[idx].joined = 0;
    }
}

// broadcast user list
static void update_and_broadcast_users() {
    char list[4096];
    list[0] = '\0';
    int first = 1;
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].fd > 0 && clients[i].joined) {
            if (!first) strncat(list, ",", sizeof(list)-strlen(list)-1);
            strncat(list, clients[i].username, sizeof(list)-strlen(list)-1);
            first = 0;
        }
    }
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].fd > 0 && clients[i].joined) {
            send_message_fd(clients[i].fd, OP_USERS, list, (uint32_t)strlen(list));
        }
    }
}

int main(int argc, char **argv) {
    int port = (argc >= 2) ? atoi(argv[1]) : SERVER_PORT_DEFAULT;

    for (int i = 0; i < MAX_CLIENTS; ++i) clients[i].fd = 0;

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) { perror("socket"); exit(1); }

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); exit(1); }
    if (listen(listen_fd, 10) < 0) { perror("listen"); exit(1); }

    printf("Server listening on port %d\n", port);

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(listen_fd, &readfds);
        int maxfd = listen_fd;

        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (clients[i].fd > 0) {
                FD_SET(clients[i].fd, &readfds);
                if (clients[i].fd > maxfd) maxfd = clients[i].fd;
            }
        }

        int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) {
            if (errno == EINTR) continue;
            perror("select"); break;
        }

        // accept new client
        if (FD_ISSET(listen_fd, &readfds)) {
            struct sockaddr_in cli_addr;
            socklen_t len = sizeof(cli_addr);
            int newfd = accept(listen_fd, (struct sockaddr*)&cli_addr, &len);
            if (newfd >= 0) {
                char ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &cli_addr.sin_addr, ip, sizeof(ip));
                printf("New connection from %s:%d (fd=%d)\n", ip, ntohs(cli_addr.sin_port), newfd);
                if (add_client(newfd) < 0) {
                    printf("Max clients reached, closing connection\n");
                    close(newfd);
                }
            }
        }

        // handle client I/O
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            int fd = clients[i].fd;
            if (fd <= 0 || !FD_ISSET(fd, &readfds)) continue;

            uint32_t be_len;
            int r = recv(fd, &be_len, sizeof(be_len), MSG_PEEK | MSG_DONTWAIT);
            if (r == 0) { remove_client_index(i); update_and_broadcast_users(); continue; }
            else if (r < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) continue;

            if (read_n(fd, &be_len, sizeof(be_len)) <= 0) { remove_client_index(i); update_and_broadcast_users(); continue; }
            uint32_t total_len = ntohl(be_len);
            if (total_len < 1) { remove_client_index(i); update_and_broadcast_users(); continue; }

            uint8_t op;
            if (read_n(fd, &op, 1) <= 0) { remove_client_index(i); update_and_broadcast_users(); continue; }

            uint32_t payload_len = total_len - 1;
            char *payload = NULL;
            if (payload_len > 0) {
                payload = (char*)malloc(payload_len + 1);
                if (read_n(fd, payload, payload_len) <= 0) { free(payload); remove_client_index(i); update_and_broadcast_users(); continue; }
                payload[payload_len] = '\0';
            }

            switch (op) {
                case OP_JOIN:
                    if (payload && payload_len > 0) {
                        strncpy(clients[i].username, payload, sizeof(clients[i].username)-1);
                        clients[i].username[sizeof(clients[i].username)-1] = '\0';
                        clients[i].joined = 1;
                        update_and_broadcast_users();
                        printf("User joined: %s (fd=%d)\n", clients[i].username, fd);
                    }
                    break;

                case OP_RENAME:
                    if (payload && payload_len > 0) {
                        strncpy(clients[i].username, payload, sizeof(clients[i].username)-1);
                        clients[i].username[sizeof(clients[i].username)-1] = '\0';
                        update_and_broadcast_users();
                    }
                    break;

                case OP_SAVE:
                    {
                        const char *file = (payload && payload_len>0) ? payload : "document.html";
                        send_message_fd(fd, OP_STATUS, "saved", (uint32_t)strlen("saved"));
                        send_message_fd(fd, OP_FILE, file, (uint32_t)strlen(file));
                        printf("Client fd %d saved file %s\n", fd, file);
                    }
                    break;

                case OP_LOAD:
                    {
                        const char *file = (payload && payload_len>0) ? payload : "document.html";
                        size_t html_len = 0;
                        char *html = load_file_content(file, &html_len);
                        if (!html) html = strdup("");
                        send_message_fd(fd, OP_FILE, file, (uint32_t)strlen(file));
                        send_message_fd(fd, OP_EDIT, html, (uint32_t)html_len);
                        send_message_fd(fd, OP_STATUS, "saved", (uint32_t)strlen("saved"));
                        free(html);
                        printf("Client fd %d loaded file %s\n", fd, file);
                    }
                    break;

                case OP_EDIT:
                case OP_CLEAR:
                case OP_PING:
                    break;

                default:
                    printf("Unknown op %d from fd %d\n", op, fd);
                    break;
            }

            if (payload) free(payload);
        }
    }

    for (int i = 0; i < MAX_CLIENTS; ++i) if (clients[i].fd) close(clients[i].fd);
    close(listen_fd);
    return 0;
}
