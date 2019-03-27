#include "mytcpsocket.h"
#include <QTimer>
#include <QFile>
#include <QDebug>

MyTcpSocket::MyTcpSocket(QObject *parent) : QObject(parent)
{

}



void MyTcpSocket::doConnect()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "Connecting...";

    // this is not blocking call
    socket->connectToHost(serw_ip, 9999);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
        emit rozlonczdo();
    }
}

void MyTcpSocket::connected()
{
    qDebug() << "Connected...";
   // QTimer::singleShot(1000, this, SLOT(authorize()));
    authorize();
}
void MyTcpSocket::authorize()
{
    socket->write(token.toUtf8());
    socket->flush();
}

void MyTcpSocket::disconnected()
{
    qDebug() << "Disconnected...";
    emit rozlonczdo();
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    //qDebug() << bytes << " Bytes written...";
}

void MyTcpSocket::readyRead()
{
    //qDebug() << "Reading...";
    // read the data from the socket
    QString zwrot = socket->readLine();
    //qDebug()<<zwrot;
    if(zwrot == "Authorized")
    {
        //qDebug()<<"ip: "<<name;
        //qDebug()<<name.toUtf8();
        socket->write(name.toUtf8());
        socket->flush();
    }
    else if(zwrot=="Unauthorized connection")
    {
        qDebug()<<"Błąd autoryzacji";
    }
    else if(zwrot != "")
    {
        dane = zwrot;
        emit dostepne_dane();
    }
}
