#include "client.h"
#include "ui_client.h"
#include <QApplication>
#include <QCoreApplication>
#include "mytcpsocket.h"
#include <QTimer>
#include <QFile>

client::client()
{
   // ui->setupUi(this);
}

client::~client()
{
   // delete ui;
}

void client::watch()
{
    /*
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(startUpdate()));
    timer->start(1800000);

    QTimer *force=new QTimer(this);
    connect(force,SIGNAL(timeout()),this,SLOT(forceCheck()));
    force->start(1000);
    */
    qDebug()<<"Pracownia-client - development release pracownia.tuxdev.com";
    qDebug()<<"Autorzy Jakub Wolski i Jakub Poplawski";
    qDebug()<<"https://github.com/123kubix123/pracownia-client kod źródłowy na licencji GPLv3";
    s = new MyTcpSocket(this);
    QString line;
    QFile config("/opt/pracownia/bin/config.conf");
        if (config.open(QIODevice::ReadOnly))
        {
           QTextStream stream(&config);
           while (!stream.atEnd())
           {
              line = stream.readLine(0);
              break;
           }
           config.close();
        }
        QStringList splitter = line.split("=");
        if(line != "" && splitter.size() == 3)
        {
           // qDebug()<<"null";
            s->token = splitter.at(0);
           // qDebug()<<"lol";
            s->name =  splitter.at(1);
           // qDebug()<<"lol";
            serw_ip = splitter.at(2);
           // qDebug()<<"lol";
            s->serw_ip = serw_ip;
           // qDebug()<<"lol";
        }
        //qDebug()<<"lol";
        connect(s, SIGNAL(rozlonczdo()),this , SLOT(reconnect()));
        connect(s, SIGNAL(dostepne_dane()), this, SLOT(run_sync()));
        s->doConnect();

}


void client::run_sync()
{
    QString Qpolecenie = s->dane;
    if(Qpolecenie == "active")
    {
        QString active = "active";
        s->socket->write(active.toUtf8());
        s->socket->flush();
    }
    else if(Qpolecenie.startsWith("z_panelu:"))
    {
        QString polecenie = Qpolecenie;
        polecenie.replace("z_panelu:","");
        QString feedback = s->name+" rozpoczyna wykonanie zadanej akcji.";
        s->socket->write(feedback.toUtf8());
        s->socket->flush();
        qDebug()<<"Rozpoczęcie wykonania zadanej akcji...";
        // wątek z wykonaniem

           QThread* thread = new QThread;
           //synchronizator_worker* worker = new synchronizator_worker(server,port,base,dir);
           synchronizator_worker* worker = new synchronizator_worker(polecenie.toStdString());
           worker->moveToThread(thread);
           //connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
           connect(thread, SIGNAL(started()), worker, SLOT(sychronize()));
           connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
           connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
           connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
           connect(thread, SIGNAL(finished()), this, SLOT(koniec_synchronizacji()));
           thread->start();
    }
    else
    {
    QStringList pol_splitted = Qpolecenie.split("`");
    if(pol_splitted.size() == 2)
    {
        QString polecenie = pol_splitted.at(0)+serw_ip+pol_splitted.at(1);
        //qDebug()<<"Polecenie: "<<polecenie;
        QString feedback = s->name+" rozpoczyna synchronizacje.";
        s->socket->write(feedback.toUtf8());
        s->socket->flush();
        qDebug()<<"Rozpoczęcie synchronizacji...";
        //qDebug()<<polecenie;
        // wątek z wykonaniem

           QThread* thread = new QThread;
           //synchronizator_worker* worker = new synchronizator_worker(server,port,base,dir);
           synchronizator_worker* worker = new synchronizator_worker(polecenie.toStdString());
           worker->moveToThread(thread);
           //connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
           connect(thread, SIGNAL(started()), worker, SLOT(sychronize()));
           connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
           connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
           connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
           connect(thread, SIGNAL(finished()), this, SLOT(koniec_synchronizacji()));
           thread->start();

    }
    }
}


void client::koniec_synchronizacji()
{
    QString feedback = s->name+" zakonczył wykonywanie zadanej akcji.";
    s->socket->write(feedback.toUtf8());
    s->socket->flush();
    qDebug()<<"Wykonywanie zakonczone... ";
}

void client::reconnect()
{
    qDebug()<<"Problem z komunikacją z serwerem następna próba połączenia za minutę...";
    QTimer::singleShot(60000, s, SLOT(doConnect()));
}

