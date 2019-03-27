#include "client.h"
#include <QCoreApplication>

QString argument;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    client w;
    w.watch();
    return a.exec();
}




