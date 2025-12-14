#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 2000
#define BUFFER_SIZE 4096

int parseRequest(char* requestFromClient, int requestSize, char* string, int stringSize)
{
    char *charPtr[4], *end;

    requestFromClient[requestSize - 1] = '\0';

    end = strstr(requestFromClient, "\r\n\r\n");
    if (!end)
        end = strstr(requestFromClient, "\n\n");
    if (!end)
        return -1;

    *(end + 4) = '\0';

    charPtr[0] = requestFromClient;
    charPtr[1] = strchr(requestFromClient, ' ');
    if (!charPtr[1]) return -1;

    charPtr[2] = strchr(charPtr[1] + 1, ' ');
    if (!charPtr[2]) return -1;

    charPtr[3] = strchr(charPtr[2] + 1, '\r');
    if (!charPtr[3]) return -1;

    *charPtr[1] = '\0';
    *charPtr[2] = '\0';
    *charPtr[3] = '\0';

    if (strcmp(charPtr[0], "GET") != 0)
        return -1;

    if (strcmp(charPtr[2] + 1, "HTTP/1.1") != 0 &&
        strcmp(charPtr[2] + 1, "HTTP/1.0") != 0)
        return -1;

    strncpy(string, charPtr[1] + 2, stringSize);

    if (string[stringSize - 1] != '\0') {
        fprintf(stderr, "parseRequest: buffer too small\n");
        exit(3);
    }

    if (*(charPtr[1] + 2) == '\0')
        strcpy(string, "index.html");

    return 0;
}

const char* getContentType(const char* filename)
{
    const char *ext = strrchr(filename, '.');
    if (!ext) return "text/plain";

    if (!strcmp(ext, ".html") || !strcmp(ext, ".htm")) return "text/html";
    if (!strcmp(ext, ".txt")) return "text/plain";
    if (!strcmp(ext, ".png")) return "image/png";
    if (!strcmp(ext, ".jpg") || !strcmp(ext, ".jpeg")) return "image/jpeg";
    if (!strcmp(ext, ".gif")) return "image/gif";
    if (!strcmp(ext, ".css")) return "text/css";
    if (!strcmp(ext, ".js")) return "application/javascript";

    return "application/octet-stream";
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    char buffer[BUFFER_SIZE];
    char fileName[256];

    FILE *fp;
    int bytesRead;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server pornit pe portul %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        memset(buffer, 0, sizeof(buffer));

        int total = 0, n;
        while ((n = read(new_socket, buffer + total,
                         sizeof(buffer) - 1 - total)) > 0) {
            total += n;
            buffer[total] = '\0';

            if (strstr(buffer, "\r\n\r\n") || strstr(buffer, "\n\n"))
                break;
        }

        printf("Cerere primită:\n%s\n", buffer);

        if (parseRequest(buffer, sizeof(buffer), fileName, sizeof(fileName)) < 0) {
            const char *error =
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: text/plain\r\n\r\n"
                "Bad Request\n";
            write(new_socket, error, strlen(error));
            close(new_socket);
            continue;
        }

        printf("Fișier cerut: %s\n", fileName);

        fp = fopen(fileName, "rb");
        if (!fp) {
            const char *notfound =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n\r\n"
                "File not found\n";
            write(new_socket, notfound, strlen(notfound));
            close(new_socket);
            continue;
        }

        char header[256];
        snprintf(header, sizeof(header),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: %s\r\n\r\n",
                 getContentType(fileName));

        write(new_socket, header, strlen(header));

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0)
            write(new_socket, buffer, bytesRead);

        fclose(fp);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}

