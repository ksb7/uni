#include "ClientNetwork.h"
#include "Protocol.h"
#include "ClientGUI.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <cstring>
#include <cstdlib>

#include <QMetaObject>

 // Global GUI pointer
extern ClientGUI *gui;

static int sockfd = -1;
static pthread_t recv_thread;
static int running = 0;

// Send message
static int send_message(uint8_t op, const void *payload, uint32_t len) {
    if (sockfd < 0) return -1;
    uint32_t total_len = 1 + len;
    uint32_t be_len = htonl(total_len);
    if (::send(sockfd, &be_len, sizeof(be_len), 0) != sizeof(be_len)) return -1;
    if (::send(sockfd, &op, 1, 0) != 1) return -1;

    const char *p = (const char*)payload;
    uint32_t left = len;
    while (left > 0) {
        ssize_t s = ::send(sockfd, p, left, 0);
        if (s <= 0) return -1;
        p += s; left -= s;
    }
    return 0;
}

int connect_to_server(const char *ip, int port, const char *username) {
    struct sockaddr_in serv{};
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv.sin_addr) <= 0) { close(sockfd); sockfd=-1; return -1; }
    if (::connect(sockfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) { close(sockfd); sockfd=-1; return -1; }

    if (username) send_message(OP_JOIN, username, (uint32_t)strlen(username));
    return 0;
}

// Send functions
void send_edit_to_server(const QString &text) {
    QByteArray ba = text.toUtf8();
    send_message(OP_EDIT, ba.constData(), (uint32_t)ba.size());
}

void send_clear_request() {
    send_message(OP_CLEAR, nullptr, 0);
}

void send_username_change_request(const QString &name) {
    QByteArray ba = name.toUtf8();
    send_message(OP_RENAME, ba.constData(), (uint32_t)ba.size());
}

// new: request server to save current document under filename (broadcasts happen server-side)
void send_save_request(const QString &filename) {
    QByteArray ba = filename.toUtf8();
    send_message(OP_SAVE, ba.constData(), (uint32_t)ba.size());
}

// new: request server to load filename and broadcast its content
void send_load_request(const QString &filename) {
    QByteArray ba = filename.toUtf8();
    send_message(OP_LOAD, ba.constData(), (uint32_t)ba.size());
}

// Read exactly
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

// Receive loop
static void* recv_loop(void*) {
    while (running) {
        uint32_t be_len;
        if (read_n(sockfd, &be_len, sizeof(be_len)) <= 0) break;
        uint32_t total_len = ntohl(be_len);
        if (total_len < 1) continue;

        uint8_t op;
        if (read_n(sockfd, &op, 1) <= 0) break;

        uint32_t payload_len = total_len - 1;
        char *payload = nullptr;
        if (payload_len > 0) {
            payload = (char*)malloc(payload_len + 1);
            if (read_n(sockfd, payload, payload_len) <= 0) { free(payload); break; }
            payload[payload_len] = '\0';
        }

        // Thread-safe GUI update
        switch (op) {
            case OP_EDIT:
                QMetaObject::invokeMethod(gui, "applyRemoteEdit", Qt::QueuedConnection,
                                          Q_ARG(QString, QString::fromUtf8(payload ? payload : "", payload_len)));
                break;
            case OP_CLEAR:
                QMetaObject::invokeMethod(gui, "applyRemoteClear", Qt::QueuedConnection);
                break;
            case OP_USERS:
                QMetaObject::invokeMethod(gui, "updateUserList", Qt::QueuedConnection,
                                          Q_ARG(QString, QString::fromUtf8(payload ? payload : "", payload_len)));
                break;
            case OP_FILE:
                QMetaObject::invokeMethod(gui, "onFileChanged",
                                        Qt::QueuedConnection,
                                        Q_ARG(QString, QString::fromUtf8(payload ? payload : "", payload_len)));
                break;
            case OP_STATUS:
                QMetaObject::invokeMethod(gui, "onStatusChanged",
                                        Qt::QueuedConnection,
                                        Q_ARG(QString, QString::fromUtf8(payload ? payload : "", payload_len)));
                break;
            default:
                break;
        }

        if (payload) free(payload);
    }
    if (sockfd >= 0) { close(sockfd); sockfd = -1; }
    return nullptr;
}

// Start / stop
void client_network_init(const char *ip, int port) {
    connect_to_server(ip, port, "Guest");
}

void client_network_start() {
    running = 1;
    pthread_create(&recv_thread, nullptr, recv_loop, nullptr);
}

void client_network_stop() {
    running = 0;
    pthread_cancel(recv_thread);
    pthread_join(recv_thread, nullptr);
    if (sockfd >= 0) close(sockfd);
}
