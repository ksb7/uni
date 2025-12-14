#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);

    static bool saveLocal(const QString &fileName, const QString &content);
    static QString loadLocal(const QString &fileName, bool &ok);

signals:
    void fileSavedToServer(const QString &fileName);
    void fileLoadedFromServer(const QString &fileName, const QString &content);
    void errorOccurred(const QString &msg);

public slots:
    void saveToServer(const QString &fileName, const QString &content);
    void loadFromServer(const QString &fileName);

private:
    QString serverHost = "192.168.100.11"; // change to your server IP
    quint16 serverPort = 12345;            // change to your server port
};

#endif // FILEMANAGER_H
