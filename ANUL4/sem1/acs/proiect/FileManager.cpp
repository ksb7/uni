#include "FileManager.h"
#include "NetworkWorker.h"
#include <QFile>
#include <QTextStream>

FileManager::FileManager(QObject *parent) : QObject(parent)
{
}

bool FileManager::saveLocal(const QString &fileName, const QString &content)
{
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&f);
    out << content;
    f.close();
    return true;
}

QString FileManager::loadLocal(const QString &fileName, bool &ok)
{
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ok = false;
        return "";
    }
    QTextStream in(&f);
    QString content = in.readAll();
    f.close();
    ok = true;
    return content;
}

void FileManager::saveToServer(const QString &fileName, const QString &content)
{
    NetworkWorker *worker = new NetworkWorker();
    worker->setServerInfo(serverHost, serverPort);

    connect(worker, &NetworkWorker::fileSent, this, [=](const QString &f){
        emit fileSavedToServer(f);
        worker->quit(); worker->deleteLater();
    });

    connect(worker, &NetworkWorker::errorOccurred, this, [=](const QString &msg){
        emit errorOccurred(msg);
        worker->quit(); worker->deleteLater();
    });

    worker->sendFile(fileName, content);
}

void FileManager::loadFromServer(const QString &fileName)
{
    // Not implemented in this example
    emit errorOccurred("Server load not implemented yet");
}
