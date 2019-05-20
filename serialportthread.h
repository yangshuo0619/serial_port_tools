#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H

#include <QObject>
#include <QThread>
#include <QtCore>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPortThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialPortThread(QObject *parent = 0);
    ~SerialPortThread();

public:
    void run();
    bool stop=false;
    void setSerialPortInfo(QSerialPort *serial_port);
signals:
    void ReadSerialPortData(QByteArray data);

private:
    QSerialPort *serial_port;
    QMutex mutex;
};

#endif // SERIALPORTTHREAD_H
