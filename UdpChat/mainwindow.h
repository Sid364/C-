#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <nicknamewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initSocket();
    enum MessageType {
        USUAL_MESSAGE,
        PERSON_APPEARD,
        PERSON_LEFT,
        WHO_IS_ONLINE
    };
    void send(QString, qint8);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    bool isConnected = false;
    QString nickname = "unknown";
    NicknameWidget nick;
public slots:
    closing();
private slots:
    void returnPressed();
    void read();
    void setConnection();
    void exit();
    void shutConnection();
    void nicknameChanged(QString nick);
    void openNicknameWidget();
};

#endif // MAINWINDOW_H
