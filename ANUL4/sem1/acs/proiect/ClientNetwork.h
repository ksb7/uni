#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H

#include <pthread.h>

int connect_to_server(const char *ip, int port);
void *receive_loop(void *arg);
void send_edit(const char *text);

#endif
