#include "ClientNetwork.h"
#include "Protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int sockfd;
#ifdef __cplusplus
extern "C" {
#endif
void apply_remote_edit(const char *text);
#ifdef __cplusplus
}
#endif

int connect_to_server(const char *ip, int port) {
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        return -1;
    }

    printf("Connected to server.\n");
    return 0;
}

void *receive_loop(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int valread = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (valread > 0) {
            buffer[valread] = '\0';
            apply_remote_edit(buffer);
        }
    }
    return NULL;
}

void send_edit(const char *text) {
    char message[BUFFER_SIZE];
    snprintf(message, sizeof(message), "%s:%s", MSG_EDIT, text);
    send(sockfd, message, strlen(message), 0);
}
