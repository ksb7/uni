#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTimer>
#include <QString>
#include <pthread.h>
#include "ClientNetwork.h"

QTextEdit *editor;
bool ignoreChange = false;

extern "C" void apply_remote_edit(const char *text) {
    QString qText = QString::fromUtf8(text);
    QMetaObject::invokeMethod(editor, [qText]() {
        ignoreChange = true;
        editor->setPlainText(qText);
        ignoreChange = false;
    });
}

void onTextChanged() {
    if (!ignoreChange) {
        QString text = editor->toPlainText();
        send_edit(text.toUtf8().data());
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    connect_to_server(argv[1], atoi(argv[2]));
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_loop, NULL);

    QApplication app(argc, argv);
    QMainWindow window;
    QWidget *central = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(central);

    editor = new QTextEdit();
    layout->addWidget(editor);
    window.setCentralWidget(central);

    QObject::connect(editor, &QTextEdit::textChanged, &onTextChanged);

    window.setWindowTitle("Collaborative Text Editor");
    window.resize(500, 400);
    window.show();

    return app.exec();
}
