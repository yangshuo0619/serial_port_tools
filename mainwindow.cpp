#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    initView();
}

void MainWindow::initView()
{
    // init serial port index view
    ui->cbSerialPortIndex->clear();
    for (int i=0;i<10;i++)
    {
        ui->cbSerialPortIndex->addItem(tr("/dev/ttyUSB")+ QString::number(i));
    }
    // init serial port baud rate view
    ui->leSerialPortBaudRate->setText(QString::number(115200));
    ui->btnWriteData->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenSerialPort_clicked()
{
    QString btn_current_Str = ui->btnOpenSerialPort->text();
    QString str_open = "打开";
    QString str_close = "关闭";
    if(QString::compare(btn_current_Str,str_open) == 0)
    {
        serial_port = new QSerialPort();
        serial_port->setPortName(ui->cbSerialPortIndex->currentText());
        serial_port->open(QIODevice::ReadWrite);
        ui->btnOpenSerialPort->setText(str_close);
        ui->btnWriteData->setEnabled(true);
    }else{
        serial_port->close();
        ui->btnOpenSerialPort->setText(str_open);
        ui->btnWriteData->setEnabled(false);
    }

}

void MainWindow::on_btnWriteData_clicked()
{
    QString str_write_data = ui->teWriteData->toPlainText();
    QByteArray bytearr_write_data = str_write_data.toUtf8().toHex();
    serial_port->write(bytearr_write_data);
    QByteArray bytearr_read_data = serial_port->readAll();
    QString str_read_data(bytearr_read_data.fromHex(bytearr_read_data));
    ui->textReadData->setText(str_read_data);
}
