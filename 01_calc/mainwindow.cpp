#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *button[15] = {
        ui->pushButton,
        ui->pushButton_2,
        ui->pushButton_3,
        ui->pushButton_4,
        ui->pushButton_5,
        ui->pushButton_6,
        ui->pushButton_7,
        ui->pushButton_8,
            ui->pushButton_9,
            ui->pushButton_10,
            ui->pushButton_11,
            ui->pushButton_12,
            ui->pushButton_13,
            ui->pushButton_14,
            ui->pushButton_15
    };

    int i=0;
    for(i=0;i<15;i++) {
        connect(button[i],
                SIGNAL(clicked()),
                this,
                SLOT(slot1()));
    }
}

int parse(string s) {
    if(s.find('+')!=-1) {
        return parse(s.substr(0,s.find('+')))+parse(s.substr(s.find('+')+1,s.length()));
    } else if(s.find_last_of('-')!=-1) {
        return parse(s.substr(0,s.find_last_of('-')))-parse(s.substr(s.find_last_of('-')+1,s.length()));
    }
    else if(s.find('*')!=-1) {
        return parse(s.substr(0,s.find('*')))*parse(s.substr(s.find('*')+1,s.length()));
    } else if(s.find_last_of('/')!=-1) {
        return parse(s.substr(0,s.find_last_of('/')))/parse(s.substr(s.find_last_of('/')+1,s.length()));
    }
    else {
        return atoi(s.c_str());
    }
}

void MainWindow::slot1()
{
    QPushButton *button = (QPushButton *) sender();
    QString s = ui->lineEdit->text();
    QString value = button->text();

    if(value.compare("="))
    {
        s += value;
    } else {
        int value=parse(s.toStdString());
        s.setNum(value);
    }

    ui->lineEdit->setText(s);
}

MainWindow::~MainWindow()
{
    delete ui;
}
