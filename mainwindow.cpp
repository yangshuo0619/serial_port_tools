#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initView();
    spThread = new SerialPortThread(this);
    QObject::connect(spThread,SIGNAL(ReadSerialPortData(QByteArray)),this,SLOT(onNewSerialPortData(QByteArray)));

}

void MainWindow::onNewSerialPortData(QByteArray data)
{
    if(!data.isEmpty())
    {
        QString str_read_data(data);
        ui->textReadData->insertPlainText(str_read_data);
        ui->textReadData->moveCursor(QTextCursor::End);
    }
}

void MainWindow::initView()
{
    // init serial port index view
    ui->cbSerialPortIndex->clear();
    foreach(const QSerialPortInfo &portinfo,QSerialPortInfo::availablePorts())
    {
        ui->cbSerialPortIndex->addItem(portinfo.portName());
    }
    ui->cbSerialPortIndex->setCurrentIndex(0);
    // init serial port baud rate view
    ui->leSerialPortBaudRate->setText(QString::number(115200));
    ui->btnWriteData->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serial_port;
    delete spThread;

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
        qint32 baud_rate = ui->leSerialPortBaudRate->text().toInt();
        serial_port->setBaudRate(baud_rate,QSerialPort::AllDirections);//设置波特率和读写方向
        serial_port->setDataBits(QSerialPort::Data8);      //数据位为8位
        serial_port->setFlowControl(QSerialPort::NoFlowControl);//无流控制
        serial_port->setParity(QSerialPort::NoParity); //无校验位
        serial_port->setStopBits(QSerialPort::OneStop); //一位停止位
        ui->btnOpenSerialPort->setText(str_close);
        ui->btnWriteData->setEnabled(true);
        spThread->setSerialPortInfo(serial_port);
        spThread->start();
        spThread->stop=false;
    }else{
        serial_port->close();
        ui->btnOpenSerialPort->setText(str_open);
        ui->btnWriteData->setEnabled(false);
        spThread->stop=true;
    }

}

void MainWindow::on_btnWriteData_clicked()
{
    QString str_write_data = ui->teWriteData->toPlainText();
    QByteArray bytearr_write_data = str_write_data.toUtf8();
    serial_port->write(bytearr_write_data);
}

void MainWindow::on_btnClearReadData_clicked()
{
    ui->textReadData->clear();
    ui->teWriteData->clear();
}
