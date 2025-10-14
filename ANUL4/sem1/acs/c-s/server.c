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

typedef struct Task {
    int id;
    char description[256];
    boolean done;
    struct Task *next;
} Task;

Task *head = NULL;
int next_id = 1;

void add_task(const char *desc) {
    Task *new_task = malloc(sizeof(Task));
    new_task->id = next_id++;
    strncpy(new_task->description, desc, sizeof(new_task->description));
    new_task->done = FALSE;
    new_task->next = head;
    head = new_task;
}

char* list_tasks() {
    static char buffer[1024];
    buffer[0] = '\0';
    Task *cur = head;
    while (cur) {
        char line[300];
        snprintf(line, sizeof(line), "[%d] %s %s\n", cur->id,
                 cur->done ? "(done)" : "(pending)", cur->description);
        strcat(buffer, line);
        cur = cur->next;
    }
    if (strlen(buffer) == 0) strcpy(buffer, "No tasks.\n");
    return buffer;
}

void mark_done(int id) {
    Task *cur = head;
    while (cur) {
        if (cur->id == id) {
            cur->done = TRUE;
            return;
        }
        cur = cur->next;
    }
}

void remove_task(int id) {
    Task **cur = &head;
    while (*cur) {
        if ((*cur)->id == id) {
            Task *tmp = *cur;
            *cur = (*cur)->next;
            free(tmp);
            return;
        }
        cur = &((*cur)->next);
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[BUF_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server started on port %d\n", PORT);

    while (1) {
        socklen_t addrlen = sizeof(address);
        client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);

        while (1) {
            memset(buffer, 0, BUF_SIZE);
            int bytes = read(client_fd, buffer, BUF_SIZE - 1);
            if (bytes <= 0) break;

            buffer[strcspn(buffer, "\n")] = 0;

            if (strncmp(buffer, "ADD ", 4) == 0) {
                add_task(buffer + 4);
                write(client_fd, "Task added.\n", 12);
            } else if (strcmp(buffer, "LIST") == 0) {
                char *list = list_tasks();
                write(client_fd, list, strlen(list));
            } else if (strncmp(buffer, "DONE ", 5) == 0) {
                mark_done(atoi(buffer + 5));
                write(client_fd, "Task marked as done.\n", 21);
            } else if (strncmp(buffer, "REMOVE ", 7) == 0) {
                remove_task(atoi(buffer + 7));
                write(client_fd, "Task removed.\n", 14);
            } else if (strcmp(buffer, "QUIT") == 0) {
                write(client_fd, "Bye!\n", 5);
                close(client_fd);
                break;
            } else {
                write(client_fd, "Unknown command.\n", 17);
            }
        }
    }
}
