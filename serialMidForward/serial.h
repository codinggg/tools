#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>

#include <QtSerialPort/qserialport.h>

typedef struct
{
	int m_nLogLine;
    int  m_nMessageId;
    FILE *g_fpLogFile;

    int			m_nMaxLogLine;
    int         m_nLog;
	
}CFG;



class serial : public QObject
{
    Q_OBJECT
public:
    serial();
    ~serial();

private slots:
    void recSerialData();
    void recSerialData1();

private:
    void LogMesg(int nSessionID, const char *szLogMesg);
    QSerialPort *myserial, *myserial1;

    CFG g_stCfg;
};

#endif // SERIAL_H
