#ifndef NICKNAMEWIDGET_H
#define NICKNAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class NicknameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NicknameWidget(QWidget *parent = 0);
    ~NicknameWidget();
private:
    QLabel *statusLabel;
    QPushButton *okButton;
    QLineEdit *lineEdit;
signals:
    newNickname(QString nick);

public slots:
    void done();
};

#endif // NICKNAMEWIDGET_H
