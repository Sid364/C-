#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QScrollBar>
#include <nicknamewidget.h>
#include <QColor>
#include <QTextCursor>
#include <QTextTable>
#include <QTextCharFormat>
#include <QListWidgetItem>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
    ui->textEdit->setReadOnly(true);
    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(setConnection()));
    connect(ui->actionExit, SIGNAL(triggered()),this, SLOT(exit()));
    connect(ui->actionSet_Nick, SIGNAL(triggered()), this, SLOT(openNicknameWidget()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(shutConnection()));

}

MainWindow::~MainWindow() {
    delete ui;
}

MainWindow::closing() {
    send("i go away", PERSON_LEFT);
}
void MainWindow::returnPressed() {
    QString message;
    message = ui->lineEdit->text();
    send(message, USUAL_MESSAGE);
    QScrollBar *sb = ui->textEdit->verticalScrollBar();
    sb->setValue(sb->maximum());
    ui->lineEdit->setText("");

}
void MainWindow::initSocket() {
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::AnyIPv4, 2525,  QUdpSocket::ReuseAddressHint);
    socket->joinMulticastGroup(QHostAddress("239.255.43.21"));
    socket->setSocketOption(QAbstractSocket::MulticastTtlOption, 50);
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(read()));
}
void MainWindow::read() {
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    socket->readDatagram(datagram.data(), datagram.size(), address);
    QDataStream in(&datagram, QIODevice::ReadOnly);
    QString str;
    qint8 type = USUAL_MESSAGE;
    QString from;
    QColor color = ui->textEdit->textColor();
    in >> type >> from >> str;

    if (type == USUAL_MESSAGE) {
        ui->textEdit->insertHtml("<br><font color = \"green\">" + from + ": " + "<font color = \"black\">" + str);
        QScrollBar *sb = ui->textEdit->verticalScrollBar();
        sb->setValue(sb->maximum());
    } else if (type == PERSON_APPEARD) {
        QList<QListWidgetItem*> list = ui->listWidget->findItems(from, Qt::MatchExactly);
       if (!list.isEmpty())
            return;
        ui->listWidget->addItem(from);\
        ui->textEdit->setTextColor(Qt::gray);
        ui->textEdit->append(from +  " has joined us");
        ui->textEdit->setTextColor(color);
    } else if (type == PERSON_LEFT) {
        QList<QListWidgetItem*> list = ui->listWidget->findItems(from, Qt::MatchExactly);
        if (list.isEmpty())
            return;
        delete list.at(0);
        ui->textEdit->setTextColor(Qt::gray);
        ui->textEdit->append(from +  " has left");
        ui->textEdit->setTextColor(color);
    } else if (type == WHO_IS_ONLINE) {
        send("i am", PERSON_APPEARD);
    }
 }

void MainWindow::setConnection() {
    if (isConnected) {
        ui->textEdit->append("You're already connected! You can chat");
        return;
    }
    if (nickname == "unknown") {
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append("You need to choose your nicname first");
        ui->textEdit->setTextColor(Qt::black);
        return;
    }
    initSocket();
    isConnected = true;
    ui->textEdit->append("Connected");
    send("Who is online ?", WHO_IS_ONLINE);
    send("i'm here", PERSON_APPEARD);
}

void MainWindow::exit() {
    qApp->quit();
}

void MainWindow::shutConnection() {
    if (!isConnected) {
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append("You are not connected!");
        ui->textEdit->setTextColor(Qt::black);
        return;
    }
    send("i left", PERSON_LEFT);
    delete socket;
    isConnected = false;
    ui->textEdit->append("You were disconnected");
}

void MainWindow::nicknameChanged(QString newNick) {
    nickname = newNick;
    nick.hide();
}

void MainWindow::openNicknameWidget() {
    nick.show();
    connect(&nick, SIGNAL(newNickname(QString)), this, SLOT(nicknameChanged(QString)));
}

void MainWindow::send(QString str, qint8 type) {
    if (!isConnected) {
        ui->textEdit->append("I'm sorry, but you need to be connected to send messages. Press Connect in the menu.");
        return;
    }
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << type;
    out << nickname;
    out << str;
    socket->writeDatagram(data, QHostAddress("239.255.43.21"), 2525);
}
