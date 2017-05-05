#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// connect server
void MainWindow::slot2()
{

    QString ip = ui->lineEdit_4->text();

    QString port = ui->lineEdit_3->text();

   this->tcpSocket = new QTcpSocket(this);

    tcpSocket->abort();

    tcpSocket->connectToHost(ip,port.toInt());

   //这里我是采用程序启动就自访问服务端（也可根据实际情况采用手动连接手动输入服务端ip的方式。）
   connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));

    //readyRead()表示服务端发送数据过来即发动信号，接着revData()进行处理。
   connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),

           this,SLOT(displayError(QAbstractSocket::SocketError)));
}

void MainWindow::slot1()
{
    QString s = ui->lineEdit_2->text();
    this->tcpSocket->write(s.toLatin1());
    qDebug() << "client send: " << s;
}

void MainWindow::revData()
{
   QString datas = tcpSocket->readAll();

//接收字符串数据。

   ui->lineEdit->setText(datas);

     //显示字符串数据。

}






void MainWindow::displayError(QAbstractSocket::SocketError)

{

   qDebug()<<tcpSocket->errorString();

   tcpSocket->close();

}
