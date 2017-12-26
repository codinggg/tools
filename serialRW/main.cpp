#include <QApplication>
#include "serial.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serial se;
    return a.exec();
}
