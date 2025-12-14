#include <QApplication>
#include "ClientGUI.h"
#include "ClientNetwork.h"

ClientGUI *gui = nullptr; // global pointer used in network thread

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    gui = new ClientGUI();
    gui->show();

    client_network_init("192.168.100.11", 8080);
    client_network_start();

    int ret = app.exec();

    client_network_stop();
    return ret;
}
