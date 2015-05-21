#include "nicknamewidget.h"
#include <QtWidgets>

NicknameWidget::NicknameWidget(QWidget *parent) : QWidget(parent) {
    statusLabel = new QLabel(tr("Enter your nickname"));
    statusLabel->setWordWrap(true);
    okButton = new QPushButton(tr("Ok"));
    lineEdit = new QLineEdit();

    QHBoxLayout *button = new QHBoxLayout();
    button->addStretch(1);
    button->addWidget(okButton);
    button->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(button);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(done()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(done()));
    setWindowTitle("Nickname");

}

NicknameWidget::~NicknameWidget()
{

}

void NicknameWidget::done()
{
    emit newNickname(lineEdit->text());
}

