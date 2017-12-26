
// serial.cpp
#include "serial.h"
#include <QDebug>
#include <QByteArray>
#include <windows.h>
#include <time.h>

#define COM1 "COM3"
#define COM2 "COM1"
#define BAUDRATE QSerialPort::Baud9600
#define LOGPATH "d://log//%s_"

serial::serial()
{
    g_stCfg.m_nMaxLogLine = 200000;

	g_stCfg.g_fpLogFile == NULL;

    LogMesg(-1, "start serial");

    myserial = new QSerialPort();
    // 连接串口收到数据事件与读取数据函数
    connect(myserial, SIGNAL(readyRead()), this, SLOT(recSerialData()));
	myserial->setPortName(COM1);
	myserial->setBaudRate(BAUDRATE);
    myserial->setParity(QSerialPort::NoParity);
    myserial->setDataBits(QSerialPort::Data8);
    myserial->setStopBits(QSerialPort::OneStop);
    myserial->setFlowControl(QSerialPort::NoFlowControl);

    if (myserial->open(QIODevice::ReadWrite))
    {
        qDebug()<< myserial->portName() << " open success";
    } else {
        qDebug()<< myserial->portName() <<" open failed";
    }

    myserial1 = new QSerialPort();
    connect(myserial1, SIGNAL(readyRead()), this, SLOT(recSerialData1()));
	myserial1->setPortName(COM2);
	myserial1->setBaudRate(BAUDRATE);
    myserial1->setParity(QSerialPort::NoParity);
    myserial1->setDataBits(QSerialPort::Data8);
    myserial1->setStopBits(QSerialPort::OneStop);
    myserial1->setFlowControl(QSerialPort::NoFlowControl);

    if (myserial1->open(QIODevice::ReadWrite))
    {
        qDebug()<< myserial1->portName() << " open success";
    } else {
        qDebug()<< myserial1->portName() << " open failed";
    }
}

serial::~serial()
{
    delete myserial;
    myserial = 0;
    delete myserial1;
    myserial1 = 0;
}

void serial::recSerialData()
{
    char tmpstr[1024*10];
    qDebug() << "recv slot...\n";
    QByteArray ba;
    ba = myserial->readAll();
    qDebug() << "ba.size:" << ba.size() << ", ba.data:" << ba.data() << endl;
    qDebug() << "ba.toHex:" << ba.toHex().data() << endl;

    LogMesg(-1, "------------------------------------------");
    LogMesg(-1, "send_data1");
    sprintf(tmpstr, "ba.size:%d, toHex:%s", ba.size(), ba.toHex().data());
    LogMesg(-1, tmpstr);
    sprintf(tmpstr, "ba.data:%s", ba.data());
    LogMesg(-1, tmpstr);
    myserial1->write(ba); //.data());

    LogMesg(-1, "------------------------------------------");
    LogMesg(-1, "------------------------------------------");
    LogMesg(-1, "\n\n\n\n\n\n");

}

void serial::recSerialData1()
{
    char tmpstr[1024*10];
    qDebug() << "recv1 slot...\n";
    QByteArray ba;
    ba = myserial1->readAll();
    qDebug() << "ba1.size:" << ba.size() << ", ba1.data:" << ba.data() << endl;
    qDebug() << "ba1.toHex:" << ba.toHex().data() << endl;
    LogMesg(2, "------------------------------------------");
    LogMesg(2, "send_data2");
    sprintf(tmpstr, "ba.size:%d, toHex:%s", ba.size(), ba.toHex().data());
    LogMesg(2, tmpstr);
    sprintf(tmpstr, "ba.data:%s", ba.data());
    LogMesg(2, tmpstr);
    myserial->write(ba); //.data());

    LogMesg(2, "------------------------------------------");
    LogMesg(2, "\n\n\n\n\n\n");
}



void serial::LogMesg(int nSessionID, const char *szLogMesg)
{
    int nThreadId = GetCurrentThreadId();
    SYSTEMTIME systemTime;
    char szLogStr[10240];
    char szDateBuf[256];

    const unsigned int datebufSize = 256;
    struct { int tv_sec; int tv_usec; } tv = { 0, 0 };
    time((time_t *)(&tv.tv_sec));
    GetLocalTime(&systemTime);
    tv.tv_usec = systemTime.wMilliseconds * 1000;

    const time_t timeInSeconds = (time_t)tv.tv_sec;
    strftime(szDateBuf,
        datebufSize,
        "%Y%m%d%H%M%S",
        localtime(&timeInSeconds));
    char msbuf[5];
    sprintf(msbuf, ".%3.3ld", long(tv.tv_usec / 1000));
    int datebufCharsRemaining = datebufSize - strlen(szDateBuf);
    strncat(szDateBuf, msbuf, datebufCharsRemaining - 1);
    szDateBuf[datebufSize - 1] = '\0';
    g_stCfg.m_nLogLine++;
    if (g_stCfg.g_fpLogFile == NULL || g_stCfg.m_nLogLine >= g_stCfg.m_nMaxLogLine)//20k
    {
        if (g_stCfg.g_fpLogFile != NULL)
            fclose(g_stCfg.g_fpLogFile);
        g_stCfg.m_nLogLine = 0;
        char logfile[512];
        char tmpbuf[1024];
        sprintf(logfile, LOGPATH, "airplane_");
        time_t the_time;
        struct tm *tm_ptr;
        (void)time(&the_time);
        tm_ptr = localtime(&the_time);
        strftime(tmpbuf, 50, "%Y%m%d%H%M%S", tm_ptr);
        strcat(tmpbuf, ".log");
        strcat(logfile, tmpbuf);
        g_stCfg.g_fpLogFile = fopen(logfile, "w");
    }
    if (g_stCfg.g_fpLogFile != NULL)
    {

        sprintf(szLogStr, "[%05d]T[%03d][%s], %s\n", nThreadId, nSessionID, szDateBuf, szLogMesg);

        printf(szLogStr);
        fseek(g_stCfg.g_fpLogFile, 0, SEEK_END);
        fwrite(szLogStr, strlen(szLogStr), 1, g_stCfg.g_fpLogFile);
        fflush(g_stCfg.g_fpLogFile);
    }

    return;
}

