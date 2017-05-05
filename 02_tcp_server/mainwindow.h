#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

private slots:
    void slot1(); // send data
    void slot2(); // start server
    void slot3(); // stop server

    void init(int port);
    void revData(); //接收来自服务端的数据
    void acceptConnection(); //接受客户端连接
    void displayError(QAbstractSocket::SocketError); //显示错误信息
};

#endif // MAINWINDOW_H
