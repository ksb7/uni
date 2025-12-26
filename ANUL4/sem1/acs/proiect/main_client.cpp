#include <QApplication>
#include <QTimer>
#include "ClientGUI.h"
#include "ClientNetwork.h"

ClientGUI *gui = nullptr; // global pointer folosit în thread-ul de rețea

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    gui = new ClientGUI();
    gui->show();

    // Conectare la server
    client_network_init("127.0.0.1", 8080);

    // Start thread-ul de retea după ce GUI-ul este complet construit
    QTimer::singleShot(0, []()
    {
        qDebug("Starting network thread...");
        client_network_start();
    });

    int ret = app.exec();

    client_network_stop();
    return ret;
}
