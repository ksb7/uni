#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 512
typedef enum boolean
{
    FALSE, 
    TRUE
} boolean;

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];
    boolean breakWanted = FALSE; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Connected to server. Enter commands:\n");

    do
    {
        memset(buffer, 0, BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        write(sockfd, buffer, strlen(buffer));

        if(TRUE == breakWanted)
        {
            break;
        }

        if (strncmp(buffer, "QUIT", 4) == 0) 
        {
            breakWanted = TRUE;
        }

        memset(buffer, 0, BUF_SIZE);
        int bytes = read(sockfd, buffer, BUF_SIZE - 1);
        if (bytes > 0) {
            buffer[bytes] = 0;
            printf("%s", buffer);
        }
    } while (1);

    close(sockfd);
    return 0;
}
