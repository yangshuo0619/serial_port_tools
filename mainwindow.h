#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnOpenSerialPort_clicked();

    void on_btnWriteData_clicked();

private:
    void initView();
    Ui::MainWindow *ui;
    QSerialPort *serial_port;
};

#endif // MAINWINDOW_H
