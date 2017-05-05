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

void MainWindow::slot1(QString s)
{
    qDebug() << s;

    //判断是哪一个语言
    QString lang = "zh.qm";
    if(s == "english")
    {
        lang = "lang_en.qm";
    }
    else
    {
        lang = "lang_zh.qm";
    }

    //安装语言翻译器
    static QTranslator* translator = NULL;
    if (translator != NULL)
    {
        qApp->removeTranslator(translator);
        delete translator;
        translator = NULL;
    }
    translator = new QTranslator;
    QString qmFilename = "/home/xoming/dev/study/qt/04_lang/" + lang;
    //这里用了绝对路径你要更改回来哦
    if (translator->load(qmFilename))
    {
        qApp->installTranslator(translator);
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
       case QEvent::LanguageChange:
            ui->retranslateUi(this);
            //还有其他手工更新界面的内容
        break;
       default:
        break;
    }
}
