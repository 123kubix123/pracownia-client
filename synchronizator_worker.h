#ifndef SYNCHRONIZATOR_WORKER_H
#define SYNCHRONIZATOR_WORKER_H

#include <QObject>
#include <QProcess>

class synchronizator_worker : public QObject
{
    Q_OBJECT
public:
    explicit synchronizator_worker(std::string polecenie, QObject *parent = 0);
    //explicit synchronizator_worker(std::string server, std::string port, std::string base, std::string dir, QObject *parent = 0);
    ~synchronizator_worker();

signals:
    void finished();
    void error(QString err);

private:
    //std::string server;
    //std::string port;
    //std::string base;
    //std::string dir;
    std::string polecenie;
    QProcess *synchronizator = new QProcess(this);

public slots:
    void sychronize();
    void processExited();
    void showMessageerr();
    void showMessagestd();
};

#endif // SYNCHRONIZATOR_WORKER_H
