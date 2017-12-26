#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include "form.h"
#include <QtSerialPort/qserialport.h>

class serial : public QObject
{
    Q_OBJECT
public:
    explicit serial(QObject *parent = 0);
    ~serial();
signals:

public slots:
    void readSerialData();
    void writeSerialData();
    void slot_pushButtonClicked();

private:
    QSerialPort *myserial;
    Form *myView;
};

#endif // SERIAL_H
