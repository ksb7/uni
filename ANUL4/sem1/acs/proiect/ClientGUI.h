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

class ClientGUI : public QMainWindow {
    Q_OBJECT
public:
    explicit ClientGUI(QWidget *parent = nullptr);

public slots:
    void applyRemoteEdit(const QString &text);
    void applyRemoteClear();
    void clearEditor();
    void updateUserList(const QString &list);
    void updateStatus(const QString &msg);
    void onFileChanged(const QString &fileName);
    void onStatusChanged(const QString &status);

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
    QString currentFile;
    QLabel *currentFileLabel;
    QLabel *unsavedLabel;

    // ===== Sync indicator =====
    QLabel *syncIndicator;
    QPropertyAnimation *pulseAnimation;

    // Prevent recursive sending
    bool localEdit;
};

#endif // CLIENTGUI_H
