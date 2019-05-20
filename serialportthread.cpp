#include "serialportthread.h"

SerialPortThread::SerialPortThread(QObject *parent)
{
}

SerialPortThread::~SerialPortThread()
{
}

void SerialPortThread::run()
{
    QByteArray data;
    while (!this->stop)
    {
        mutex.lock();
        data = serial_port->readAll();
        mutex.unlock();

        emit ReadSerialPortData(data);
        this->msleep(50);

    }

}

void SerialPortThread::setSerialPortInfo(QSerialPort *serial_port)
{
    this->serial_port = serial_port;
}
