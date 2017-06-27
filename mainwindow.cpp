#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QLineEdit>
#include <QButtonGroup>
#include"classfythread.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttongroup1.addButton(ui->copyradio,0);
    buttongroup1.addButton(ui->moveradio,1);
    ui->copyradio->setChecked(true);
    buttongroup1.setExclusive(true);

    buttongroup2.addButton(ui->classfyradio,0);
    buttongroup2.addButton(ui->findimageradio,1);
    ui->classfyradio->setChecked(true);
    buttongroup2.setExclusive(true);

    connect(&buttongroup1, SIGNAL(buttonClicked (int)), this, SLOT(onButtonClicked1(int)) );
    connect(&buttongroup2, SIGNAL(buttonClicked (int)), this, SLOT(onButtonClicked2(int)) );
    connect(ui->openEdit,SIGNAL(textChanged(QString)),Classfythread::Create(),SLOT(getpath(QString)));
    connect(Classfythread::Create(),SIGNAL(sendtxt(QString)),ui->showBrowser,SLOT(append(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onopenbtn()
{
    qDebug()<<"in onopenbtn()";
    QString path=QFileDialog::getExistingDirectory(this,"选择文件路径...","./",QFileDialog::ShowDirsOnly);
    if(path.isEmpty())
    {
        return;
    }else{
        ui->openEdit->setText(path);
        qDebug()<<path;
    }
}

void MainWindow::onButtonClicked1(int id)
{
    switch(id)
    {
        case 0:
            iscopy=true;
            qDebug()<<"拷贝";
            ui->showBrowser->append("切换至<拷贝>模式");
            emit sendmethod(true);
        break;
        case 1:
            iscopy=false;
            qDebug()<<"移动";
            ui->showBrowser->append("切换至<移动>模式");
            emit sendmethod(false);
        break;
    }

}

void MainWindow::onButtonClicked2(int id)
{
    switch(id)
    {
        case 0:
            isclassfy=true;
            ui->showBrowser->append("切换功能至<0k1k分类>");

        break;
        case 1:
            isclassfy=false;
            ui->showBrowser->append("切换功能至<查找原图片>");
        break;
    }
}

void MainWindow::onstartbtn()
{
    //qDebug()<<"in onstartbtn()";
    ui->startButton->setDisabled(true);
    if(isclassfy==true)
    {
        ui->showBrowser->append("0k1k分类");
        if(!ui->openEdit->text().isEmpty())
        {
            Classfythread::Create()->start();
            connect(this,SIGNAL(sendmethod(bool)),Classfythread::Create(),SLOT(getmethod(bool)));
        }
        else
        {
            ui->showBrowser->append("文件路径不能为空，请选择路径！");
        }
    }
    else
    {
        ui->showBrowser->append("查找原图片");
    }
}

void MainWindow::oncancelbtn()
{
    qDebug()<<"in oncancelbtn()";
    ui->startButton->setDisabled(false);

}
