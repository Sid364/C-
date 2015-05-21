#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <nicknamewidget.h>

namespace Ui {
class MainWindow;
}

//Represents Main Window of Char
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    // make preparations for socket
    void initSocket();
    // enumiration represent kinds of messages clint could get or send
    enum MessageType {
        USUAL_MESSAGE,
        PERSON_APPEARD,
        PERSON_LEFT,
        WHO_IS_ONLINE
    };
    //send message to other computers
    void send(QString, qint8);
    ~MainWindow();

private:
    // user interface
    Ui::MainWindow *ui;
    //UDP socket to send messages
    QUdpSocket *socket;
    // indicates if program is connected
    bool isConnected = false;
    // string representing a nickname of a Computer
    QString nickname = "unknown";
    // widget for establishing nickname
    NicknameWidget nick;
public slots:
    // Person disconnects
    void closing();
private slots:
    //'Enter' has been pressed
    void returnPressed();
    // read message and handle it
    void read();
    // set connection so client is able to send and receive messages
    void setConnection();
    // exit program
    void exit();
    //shut connection and stop receving messages
    void shutConnection();
    //invokes if nickname was changed
    void nicknameChanged(QString nick);
    //open widget to change nickname
    void openNicknameWidget();
};

#endif // MAINWINDOW_H
