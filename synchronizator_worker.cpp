#include "synchronizator_worker.h"
#include <QDebug>
#include <QThread>
#include <QProcess>
#include <iostream>

synchronizator_worker::synchronizator_worker(std::string polecenie, QObject *parent) : QObject(parent)
{
   // this->server = server;
    //this->port = port;
    //this->base = base;
    //this->dir = dir;
    this->polecenie = polecenie;
    //this->synchronizator = new QProcess;
}


synchronizator_worker::~synchronizator_worker() {

}
void synchronizator_worker::sychronize()
{
    //qDebug()<<"Worker thread: "<<QThread::currentThreadId();
     // przenieść albo na początekk klasy poza funkcje albo do konstruktora albo do headera do private i sprubować czy bedzie w wontku
    //std::string csychro = "sshpass -p 'novell' rsync -aogu -e 'ssh -i /root/id_rsa -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -p "+port+"' distribution@"+server+":"+base+"/ "+dir+" --delete-before --ignore-errors --info=progress2 --exclude 'manifest.info' 2> /var/log/freeze && exit || exit\n";
    connect(synchronizator, SIGNAL(finished(int)), this, SLOT(processExited()));
   // connect(synchronizator, SIGNAL(readyReadStandardOutput()), this, SLOT(showMessagestd()));
    connect(synchronizator, SIGNAL(readyReadStandardError()), this, SLOT(showMessageerr()));
    connect(synchronizator, SIGNAL(readyRead()), this, SLOT(showMessagestd()));
    synchronizator->start("/bin/bash");
    synchronizator->waitForStarted();
    synchronizator->write(polecenie.c_str());
   // synchronizator->waitForBytesWritten();
}

void synchronizator_worker::processExited()
{
        emit finished();
}

void synchronizator_worker::showMessageerr()
{
    QString log = synchronizator->readAllStandardError();
    log.replace("\n","");
    log.replace("\r","");
    qDebug()<<"Error rsynca: ";
    qDebug()<<log;
}


void synchronizator_worker::showMessagestd()
{
    QString log = synchronizator->readLine();
    //qDebug()<<"Standardowy output rsynca: ";
    std::cout<<log.toStdString();
}
