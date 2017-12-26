#include <QCoreApplication>
#include "serial.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    serial serl;

    return a.exec();
}
