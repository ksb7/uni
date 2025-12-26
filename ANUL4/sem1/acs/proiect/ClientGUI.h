#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include <QFontComboBox>
#include <QComboBox>
#include <QString>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPushButton>
#include "NetworkWorker.h"

class ClientGUI : public QMainWindow {
    Q_OBJECT
public:
    explicit ClientGUI(QWidget *parent = nullptr);
    void setLocalFileVersion(const QString &file, int version);
    

public slots:
    void applyRemoteEdit(const QString &html);
    void applyRemoteClear();
    void clearEditor();
    void updateUserList(const QString &list);
    void updateStatus(const QString &msg);
    void onStatusChanged(const QString &statusStr);
    QString getCurrentFile() const { return currentFile; }
    void setCurrentFile(const QString &f) { currentFile = f; currentVersion = 0; }
    void loadFromServer(const QString &html, int serverVersion);

    int getCurrentVersion() const { return currentVersion; }
    void setCurrentVersion(int v) { currentVersion = v; }
    void onServerVersion(const QString &file, int version);
    void loadFromServerCompleted();
    bool isLoadingFromServer() const;      // getter pentru loadingFromServer
    void setLocalVersion(const QString &file, int version);
    void setServerVersion(const QString &file, int version);
    void applyUsername();

    // Formatting slots
    void setBold();
    void setItalic();
    void setUnderline();
    void toggleBulletList();
    void toggleNumberList();
    void insertTable();
    void changeTextColor();
    void changeBackgroundColor();
    void changeFont(const QFont &font);
    void changeFontSize(const QString &size);

    void setOutOfDate(bool outOfDate);
    void updateFromServer(); 

private:
    // GUI elements
    QTextEdit *editor;
    QLineEdit *usernameBox;
    QListWidget *userList;
    QStatusBar *status;

    // Formatting toolbar
    QToolBar *formatBar;
    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;
    QAction *bulletAction;
    QAction *numberAction;
    QAction *tableAction;
    QAction *textColorAction;
    QAction *bgColorAction;
    QFontComboBox *fontBox;
    QComboBox *sizeBox;

    // File actions
    QAction *saveAction;
    QAction *loadAction;

    // ===== File tracking / unsaved info =====
    bool hasUnsavedChanges;
    bool isSyncing = false;
    int localVersion = 0;
    int serverVersion = 0;
    QString currentFile;
    int currentVersion = 0; // versiunea locală a fișierului curent
    QLabel *currentFileLabel;
    QLabel *unsavedLabel;
    int localFileVersion = 0;   // versiunea locală
    int serverFileVersion = 0;
    QMap<QString, int> localFileVersions;  // versiunea locală pe fișier
    QMap<QString, int> serverFileVersions; // versiunea server pe fișier
    bool loadingFromServer = false;
    bool updatingFromServer = false;
    bool applyingServerContent;
    bool ignoreServerStatusTemporarily = false;


    // ===== Sync indicator =====
    QLabel *syncIndicator;
    QPropertyAnimation *pulseAnimation;

    // ===== Out-of-date indicator =====
    QLabel *outOfDateLabel;
    QPushButton *updateBtn;

    // Prevent recursive sending
    bool localEdit;

    NetworkWorker *networkWorker;

private slots:
    void updateActiveEditors(const QString &list);
    void saveFile();
signals:
    void fileLoadedFromServer(const QString &html, int serverVersion);

};


#endif // CLIENTGUI_H
