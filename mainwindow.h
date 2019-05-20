#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "serialportthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    SerialPortThread *spThread;

private slots:
    void on_btnOpenSerialPort_clicked();

    void on_btnWriteData_clicked();
    void onNewSerialPortData(QByteArray data);

    void on_btnClearReadData_clicked();

private:
    void initView();   
    Ui::MainWindow *ui;
    QSerialPort *serial_port;
    QSerialPortInfo *info;
};

#endif // MAINWINDOW_H
