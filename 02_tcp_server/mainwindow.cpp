#include "mainwindow.h"
#include "ui_mainwindow.h"

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
// send data
void MainWindow::slot1()
{
    this->tcpSocket->write(ui->lineEdit->text().toLatin1());
}
// start
void MainWindow::slot2()
{
    QString s = ui->lineEdit_3->text();

    init(s.toInt());
}

// stop
void MainWindow::slot3()
{

}

void MainWindow::init(int port)
{
    this->tcpServer = new QTcpServer(this);
    this->tcpSocket = new QTcpSocket(this);

    //监听是否有客户端来访，且对任何来访者监听，端口为6666

      if(!tcpServer->listen(QHostAddress::Any,port))
      {
         qDebug()<<tcpServer->errorString();
         close();
         return;
      }

      qDebug() << "Server start on port:" << port;

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));


    //newConnection()用于当有客户端访问时发出信号，acceptConnection()信号处理函数
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));

    //当tcpSocket在接受客户端连接时出现错误时，displayError(QAbstractSocket::SocketError)进行错误提醒并关闭tcpSocket。
}

void MainWindow::revData()

{
   QString datas = tcpSocket->readAll();

//接收字符串数据。

   ui->lineEdit_2->setText(datas);

     //显示字符串数据。
}

void MainWindow::acceptConnection() //接受客户端连接
{
    //当有客户来访时将tcpSocket接受tcpServer建立的socket
    qDebug()<<"NEW CLIENT";
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
}

void MainWindow::displayError(QAbstractSocket::SocketError) //显示错误信息
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}
