#include "ClientGUI.h"
#include "ClientNetwork.h"
#include <QtWidgets>
#include <QTimer>
#include <QPropertyAnimation>
#include "NetworkWorker.h"  
#include "FileManager.h"

ClientGUI::ClientGUI(QWidget *parent) 
    : QMainWindow(parent), localEdit(true), hasUnsavedChanges(false) 
{
    setWindowTitle("Notes");
    resize(1000, 650);

    currentFile = "";

    QWidget *central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout();

    // ===== Sidebar =====
    QVBoxLayout *sideLayout = new QVBoxLayout();
    sideLayout->setSpacing(10);

    usernameBox = new QLineEdit();
    usernameBox->setPlaceholderText("Enter username");

    QPushButton *applyBtn = new QPushButton("Set Username");
    QPushButton *clearBtn = new QPushButton("Clear");
    QPushButton *saveBtn = new QPushButton("Save");
    QPushButton *loadBtn = new QPushButton("Load");

    sideLayout->addWidget(usernameBox);
    sideLayout->addWidget(applyBtn);
    sideLayout->addWidget(clearBtn);
    sideLayout->addWidget(saveBtn);
    sideLayout->addWidget(loadBtn);

    // ===== Info display =====
    currentFileLabel = new QLabel("File: No file");
    unsavedLabel = new QLabel("Status: Saved");

    // Wrap sync indicator in fixed-size container to prevent layout shift
    QWidget *indicatorContainer = new QWidget();
    indicatorContainer->setFixedSize(20, 20);
    QVBoxLayout *indicatorLayout = new QVBoxLayout(indicatorContainer);
    indicatorLayout->setContentsMargins(0, 0, 0, 0);
    syncIndicator = new QLabel();
    syncIndicator->setFixedSize(16, 16);
    syncIndicator->setStyleSheet("border-radius:8px; background-color:green;");
    indicatorLayout->addWidget(syncIndicator);
    indicatorLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout *infoLayout = new QVBoxLayout();
    infoLayout->setAlignment(Qt::AlignVCenter);
    infoLayout->addWidget(currentFileLabel);
    infoLayout->addWidget(unsavedLabel);

    QHBoxLayout *statusLayout = new QHBoxLayout();
    statusLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statusLayout->addWidget(indicatorContainer);
    statusLayout->addLayout(infoLayout);

    sideLayout->addLayout(statusLayout);

    sideLayout->addWidget(new QLabel("Connected Users:"));
    userList = new QListWidget();
    userList->setFixedWidth(180);
    sideLayout->addWidget(userList);
    sideLayout->addStretch();

    // ===== Editor =====
    editor = new QTextEdit();
    editor->setAcceptRichText(true);
    editor->setPlaceholderText("Start typing...");

    mainLayout->addLayout(sideLayout, 1);
    mainLayout->addWidget(editor, 4);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    // ===== Formatting toolbar =====
    formatBar = addToolBar("Format");
    boldAction = formatBar->addAction("B"); boldAction->setCheckable(true);
    italicAction = formatBar->addAction("I"); italicAction->setCheckable(true);
    underlineAction = formatBar->addAction("U"); underlineAction->setCheckable(true);
    bulletAction = formatBar->addAction("•"); bulletAction->setCheckable(true);
    numberAction = formatBar->addAction("1."); numberAction->setCheckable(true);
    tableAction = formatBar->addAction("Table");
    textColorAction = formatBar->addAction("Text Color");
    bgColorAction = formatBar->addAction("Background");

    fontBox = new QFontComboBox();
    formatBar->addWidget(fontBox);
    sizeBox = new QComboBox();
    for(int i=8;i<=24;i+=2) sizeBox->addItem(QString::number(i));
    sizeBox->setCurrentText("14");
    formatBar->addWidget(sizeBox);

    // ===== Pulsing animation for sync indicator =====
    pulseAnimation = new QPropertyAnimation(syncIndicator, "geometry", this);
    pulseAnimation->setDuration(800);
    pulseAnimation->setStartValue(QRect(0, 0, 16, 16));
    pulseAnimation->setEndValue(QRect(-2, -2, 20, 20));
    pulseAnimation->setLoopCount(-1);
    pulseAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // ===== Signals =====
    connect(editor, &QTextEdit::textChanged, [=]() {
        if(!localEdit) return;
        hasUnsavedChanges = true;
        unsavedLabel->setText("Status: Unsaved changes");
        syncIndicator->setStyleSheet("border-radius:8px; background-color:orange;");
        pulseAnimation->start();
        send_edit_to_server(editor->toHtml());
    });

    connect(applyBtn, &QPushButton::clicked, [=]() {
        QString name = usernameBox->text();
        if(!name.isEmpty()) send_username_change_request(name);
    });

    connect(clearBtn, &QPushButton::clicked, this, &ClientGUI::clearEditor);

    connect(saveBtn, &QPushButton::clicked, [=]() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File",
                                                    currentFile.isEmpty() ? "" : currentFile,
                                                    "HTML Files (*.html);;Text Files (*.txt)");
    if(fileName.isEmpty()) return;

    // Save locally
    if(FileManager::saveLocal(fileName, editor->toHtml())) {
        currentFile = fileName;
        currentFileLabel->setText("File: " + currentFile);
        unsavedLabel->setText("Status: Saved locally");
    }

    // Save to server in background
    FileManager *fm = new FileManager();
    connect(fm, &FileManager::fileSavedToServer, this, [=](const QString &f){
        status->showMessage("Saved to server: " + f);
        unsavedLabel->setText("Status: Synced");
    });
    connect(fm, &FileManager::errorOccurred, this, [=](const QString &msg){
        status->showMessage("Error saving to server: " + msg);
        unsavedLabel->setText("Status: Unsynced");
    });

    QMetaObject::invokeMethod(fm, "saveToServer", Qt::QueuedConnection,
                              Q_ARG(QString, fileName),
                              Q_ARG(QString, editor->toHtml()));
    });


    connect(loadBtn, &QPushButton::clicked, [=]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                        "", "HTML Files (*.html *.htm);;Text Files (*.txt);;All Files (*)");
        if(!fileName.isEmpty()) {
            QFile f(fileName);
            if(f.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&f);
                QString html = in.readAll();
                f.close();
                applyRemoteEdit(html); 
                send_edit_to_server(html);
                currentFile = fileName;
                currentFileLabel->setText("File: " + currentFile);
                status->showMessage("Loaded " + fileName);
            }
        }
    });

    // ===== Formatting toolbar signals =====
    connect(boldAction, &QAction::triggered, this, &ClientGUI::setBold);
    connect(italicAction, &QAction::triggered, this, &ClientGUI::setItalic);
    connect(underlineAction, &QAction::triggered, this, &ClientGUI::setUnderline);
    connect(bulletAction, &QAction::triggered, this, &ClientGUI::toggleBulletList);
    connect(numberAction, &QAction::triggered, this, &ClientGUI::toggleNumberList);
    connect(tableAction, &QAction::triggered, this, &ClientGUI::insertTable);
    connect(textColorAction, &QAction::triggered, this, &ClientGUI::changeTextColor);
    connect(bgColorAction, &QAction::triggered, this, &ClientGUI::changeBackgroundColor);
    connect(fontBox, &QFontComboBox::currentFontChanged, this, &ClientGUI::changeFont);
    connect(sizeBox, &QComboBox::currentTextChanged, this, &ClientGUI::changeFontSize);
}

// ===== Slots =====
void ClientGUI::applyRemoteEdit(const QString &html)
{
    localEdit = false;

    editor->blockSignals(true);
    editor->setHtml(html);
    editor->blockSignals(false);

    hasUnsavedChanges = false;
    unsavedLabel->setText("Status: Synced");
    syncIndicator->setStyleSheet("border-radius:8px; background-color:green;");
    pulseAnimation->stop();

    localEdit = true;
}

void ClientGUI::applyRemoteClear() {
    localEdit = false;
    editor->blockSignals(true);
    editor->clear();
    editor->blockSignals(false);
    localEdit = true;

    hasUnsavedChanges = false;
    unsavedLabel->setText("Status: Synced");
    syncIndicator->setStyleSheet("border-radius:8px; background-color:green;");
    pulseAnimation->stop();
}

void ClientGUI::clearEditor() {
    if(!localEdit) return;
    localEdit = false;
    editor->blockSignals(true);
    editor->clear();
    editor->blockSignals(false);
    localEdit = true;
    send_clear_request();

    hasUnsavedChanges = true;
    unsavedLabel->setText("Status: Unsaved changes");
    syncIndicator->setStyleSheet("border-radius:8px; background-color:orange;");
    pulseAnimation->start();
}

void ClientGUI::updateUserList(const QString &list) {
    userList->clear();
    for(const QString &n : list.split(',')) {
        if(!n.isEmpty()) userList->addItem(n);
    }
}

void ClientGUI::updateStatus(const QString &msg) {
    status->showMessage(msg);
}

void ClientGUI::onFileChanged(const QString &fileName)
{
    currentFile = fileName;
    currentFileLabel->setText("File: " + fileName);
}

void ClientGUI::onStatusChanged(const QString &status)
{
    if (status == "saved") {
        hasUnsavedChanges = false;
        unsavedLabel->setText("Status: Synced");
        syncIndicator->setStyleSheet("border-radius:8px; background-color:green;");
        pulseAnimation->stop();
    } else {
        hasUnsavedChanges = true;
        unsavedLabel->setText("Status: Unsaved");
        syncIndicator->setStyleSheet("border-radius:8px; background-color:orange;");
        pulseAnimation->start();
    }
}

// ===== Formatting =====
void ClientGUI::setBold() { QTextCharFormat fmt; fmt.setFontWeight(boldAction->isChecked()?QFont::Bold:QFont::Normal); editor->mergeCurrentCharFormat(fmt); }
void ClientGUI::setItalic() { QTextCharFormat fmt; fmt.setFontItalic(italicAction->isChecked()); editor->mergeCurrentCharFormat(fmt); }
void ClientGUI::setUnderline() { QTextCharFormat fmt; fmt.setFontUnderline(underlineAction->isChecked()); editor->mergeCurrentCharFormat(fmt); }
void ClientGUI::changeFont(const QFont &font) { QTextCharFormat fmt; fmt.setFont(font); editor->mergeCurrentCharFormat(fmt); }
void ClientGUI::changeFontSize(const QString &size) { QTextCharFormat fmt; fmt.setFontPointSize(size.toDouble()); editor->mergeCurrentCharFormat(fmt); }
void ClientGUI::toggleBulletList() { QTextCursor c=editor->textCursor(); c.beginEditBlock(); QTextListFormat l; l.setStyle(QTextListFormat::ListDisc); c.createList(l); c.endEditBlock(); }
void ClientGUI::toggleNumberList() { QTextCursor c=editor->textCursor(); c.beginEditBlock(); QTextListFormat l; l.setStyle(QTextListFormat::ListDecimal); c.createList(l); c.endEditBlock(); }
void ClientGUI::insertTable() { QTextCursor c=editor->textCursor(); c.beginEditBlock(); c.insertTable(2,2); c.endEditBlock(); }
void ClientGUI::changeTextColor() { QColor c=QColorDialog::getColor(Qt::black,this,"Text Color"); if(c.isValid()){ QTextCharFormat fmt; fmt.setForeground(c); editor->mergeCurrentCharFormat(fmt);} }
void ClientGUI::changeBackgroundColor() { QColor c=QColorDialog::getColor(Qt::white,this,"Background Color"); if(c.isValid()){ QTextCharFormat fmt; fmt.setBackground(c); editor->mergeCurrentCharFormat(fmt);} }
