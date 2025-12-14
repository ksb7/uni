#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QString>

extern "C" {
    void client_network_init(const char *ip, int port);
    void client_network_start();
    void client_network_stop();

    void send_edit_to_server(const QString &text);
    void send_clear_request();
    void send_username_change_request(const QString &name);
}

#endif
