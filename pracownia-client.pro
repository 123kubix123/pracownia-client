#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T21:23:40
#
#-------------------------------------------------

QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pracownia-client
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    synchronizator_worker.cpp \
    mytcpsocket.cpp

HEADERS  += client.h \
    synchronizator_worker.h \
    mytcpsocket.h

