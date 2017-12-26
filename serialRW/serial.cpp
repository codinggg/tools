#include "serial.h"
#include <QDebug>

serial::serial(QObject *parent) : QObject(parent)
{
    qDebug() << "serial constructor start..\n";

    myView = new Form;
    connect(myView, SIGNAL(pushButtonClicked()), this,
            SLOT(slot_pushButtonClicked()));
    myView->show();

    myserial = new QSerialPort();
    connect(myserial, SIGNAL(readyRead()), this,
            SLOT(readSerialData()));

    myserial->setPortName("COM3");
    myserial->setBaudRate(QSerialPort::Baud9600);
    myserial->setParity(QSerialPort::NoParity);
    myserial->setDataBits(QSerialPort::Data8);
    myserial->setStopBits(QSerialPort::OneStop);
    myserial->setFlowControl(QSerialPort::NoFlowControl);

    if (!myserial->open(QIODevice::ReadWrite))
    {
        // open serial failed
        qDebug() << "serial open failed.\n";
//        system("pause");
    }
}


serial::~serial()
{
    delete myserial;
    myserial = NULL;
}

void serial::readSerialData()
{
    QByteArray ba;
    ba = myserial->readAll();
    qDebug() << "serial recv size:" << ba.size()
             << "\ttoHex:" << ba.toHex()
             << "\tdata:" << ba.data() << "\n";
}



void serial::writeSerialData()
{
    QString strCmd = "0200002";

    QByteArray ba(strCmd.toStdString().c_str());
    size_t ret = myserial->write(QByteArray::fromHex(ba));
    qDebug() << "serial write size:" << ret << "\n";
}



void serial::slot_pushButtonClicked()
{
    writeSerialData();
}








