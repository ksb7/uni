#include "NetworkWorker.h"
#include <QDataStream>
#include <QDebug>
#include <QTcpSocket>

NetworkWorker::NetworkWorker(QObject *parent)
    : QThread(parent), op(None)
{
}


NetworkWorker::~NetworkWorker()
{
    if(socket) {
        socket->disconnectFromHost();
    }
    quit();
    wait();
}

void NetworkWorker::setServerInfo(const QString &host, quint16 port)
{
    serverHost = host;
    serverPort = port;
}

void NetworkWorker::sendFile(const QString &fileName, const QString &content)
{
    pendingFileName = fileName;
    pendingFileContent = content;
    op = SendFile;
    if(!isRunning()) start();
}

void NetworkWorker::requestFile(const QString &fileName)
{
    pendingFileName = fileName;
    op = RequestFile;
    if(!isRunning()) start();
}

void NetworkWorker::sendUsername(const QString &username)
{
    pendingFileName = username;
    op = SendUsername;
    if(!isRunning()) start();
}
void NetworkWorker::run()
{
    QTcpSocket socket; // socket local în thread-ul curent
    socket.connectToHost(serverHost, serverPort);

    if(!socket.waitForConnected(3000)) {
        emit errorOccurred("Cannot connect to server");
        op = None;
        return;
    }

    QDataStream out(&socket);
    out.setVersion(QDataStream::Qt_5_0);

    switch(op) {
        case SendFile:
        {
            QByteArray payload;
            QDataStream payloadStream(&payload, QIODevice::WriteOnly);
            payloadStream << pendingFileName << pendingFileContent;

            out << (quint32)payload.size();
            socket.write(payload);
            socket.flush();
            socket.waitForBytesWritten(3000);

            emit fileSent(pendingFileName);
            qDebug() << "File sent:" << pendingFileName;
            break;
        }

        case SendUsername:
        {
            QByteArray payload = pendingFileName.toUtf8(); // direct UTF-8
            out << (quint32)payload.size();
            socket.write(payload);
            socket.flush();
            socket.waitForBytesWritten(3000);

            qDebug() << "Username sent:" << pendingFileName;
            break;
        }


        case RequestFile:
            emit errorOccurred("Request file not implemented yet");
            break;

        case None:
        default:
            break;
    }

    op = None;

    // Disconnect, fără waitForDisconnected
    if(socket.state() == QAbstractSocket::ConnectedState) {
        socket.disconnectFromHost();
    }
}
