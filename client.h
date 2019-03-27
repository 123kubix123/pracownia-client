#ifndef CLIENT_H
#define CLIENT_H

#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QThread>
#include <synchronizator_worker.h>
#include "mytcpsocket.h"


class client : public QObject
{
    Q_OBJECT

public:
    explicit client();
    ~client();

private slots:
    void run_sync();
    void reconnect();
    void koniec_synchronizacji();

signals:
    void zakoncono();

public slots:
    void watch();

private:
    MyTcpSocket *s;
    QString serw_ip;
};

#endif // CLIENT_H
