#include "NetworkWorker.h"
#include <QDataStream>
#include <QDebug>

NetworkWorker::NetworkWorker(QObject *parent)
    : QThread(parent), op(None), socket(nullptr)
{
}

NetworkWorker::~NetworkWorker()
{
    if(socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
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

void NetworkWorker::run()
{
    socket = new QTcpSocket();
    socket->connectToHost(serverHost, serverPort);
    if(!socket->waitForConnected(3000)) {
        emit errorOccurred("Cannot connect to server");
        return;
    }

    QDataStream out(socket);
    out.setVersion(QDataStream::Qt_5_0);

    if(op == SendFile) {
        // Simple protocol: [len][filename][content]
        QByteArray payload;
        QDataStream payloadStream(&payload, QIODevice::WriteOnly);
        payloadStream << pendingFileName << pendingFileContent;

        out << (quint32)payload.size();
        socket->write(payload);
        socket->flush();
        if(!socket->waitForBytesWritten(3000)) {
            emit errorOccurred("Failed to send file");
        } else {
            emit fileSent(pendingFileName);
        }
    } else if(op == RequestFile) {
        // Not implemented in detail, placeholder
        emit errorOccurred("Request file not implemented yet");
    }

    socket->disconnectFromHost();
    socket->deleteLater();
    socket = nullptr;
    op = None;
}
