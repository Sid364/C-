#-------------------------------------------------
#
# Project created by QtCreator 2015-01-31T00:03:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network

TARGET = UdpChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nicknamewidget.cpp

HEADERS  += mainwindow.h \
    nicknamewidget.h

FORMS    += mainwindow.ui
