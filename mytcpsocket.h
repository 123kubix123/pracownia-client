#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = 0);

signals:
    void rozlonczdo();
    void dostepne_dane();

public slots:
    void doConnect();
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void authorize();

public:
    QTcpSocket *socket;
    QString name;
    QString dane;
    QString serw_ip;
    QString token;
};

#endif // MYTCPSOCKET_H
