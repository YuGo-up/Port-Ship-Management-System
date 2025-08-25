#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include "mainpage.h"
#include "mainpage3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->myDatabase.getconnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString userInputtype = "user";
    if(ui->radioButton_2->isChecked())
    {
        userInputtype = "船舶";
    }
    else
    {
        userInputtype = "港口";
    }
    QString userInputNumber = ui->intnumber->text();//获取用户输入的账号
    QString userInputPassWord = ui->intpassword->text();//获取用户输入的密码
    qDebug()<<"用户输入的账号"+userInputNumber;//检查用户输入的账号输出到控制台
    qDebug()<<"用户输入的密码"+userInputPassWord;//检查用户输入的密码输出到控制台
    qDebug()<<"用户输入的类别:"+userInputtype;//检查用户输入类别

    if(ui->radioButton_2->isChecked())
    {
        QSqlQuery sql;
        sql.prepare("SELECT * FROM suser where susernumber=:userInputNumbe;");//从数据库中suser表找susernumber = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",userInputNumber);//:userInputNumber为用户输入的账户
        sql.exec();//执行以上SQL语句
        QString userNumber;
        QString userPassWord;
        while(sql.next())
        {
            userNumber = sql.value("susernumber").toString();
            userPassWord = sql.value("suserpassword").toString();
        }
        qDebug()<<"数据库找到的账号"+userNumber;//如果有就输出账号
        qDebug()<<"数据库找到的密码"+userPassWord;//如果有就输出密码
        sql.clear();

        if(userInputPassWord == userPassWord && userInputNumber == userNumber)//如果用户输入的账号密码正确
        {
            qDebug()<<"登录成功！";

            this->~MainWindow();//跳出mainwindow窗口
            mainpage3 * w = new mainpage3();//定义mainpage3窗口指针
            qDebug()<<"开始跳转";
            w->show();//跳转到mainpage2窗口
            qDebug()<<"跳转成功";
            //this->myDatabase.quitConnection();//测试
        }
        else
        {
            qDebug()<<"登录失败！";
            ui->label_5->setText("登录失败！请重新输入");
        }
    }
    else
    //if(ui->radioButton->isChecked())
    {
        QSqlQuery sql;
        sql.prepare("SELECT * FROM puser where pusernumber=:userInputNumbe;");//从数据库中suser表找susernumber = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",userInputNumber);//:userInputNumber为用户输入的账户
        sql.exec();//执行以上SQL语句
        QString userNumber;
        QString userPassWord;
        while(sql.next())
        {
            userNumber = sql.value("pusernumber").toString();
            userPassWord = sql.value("puserpassword").toString();
        }
        qDebug()<<"数据库找到的账号"+userNumber;//如果有就输出账号
        qDebug()<<"数据库找到的密码"+userPassWord;//如果有就输出密码
        sql.clear();

        if(userInputPassWord == userPassWord && userInputNumber == userNumber)//如果用户输入的账号密码正确
        {
            qDebug()<<"登录成功！";
            this->~MainWindow();//跳出mainwindow窗口
            mainpage * w = new mainpage();//定义mainpage窗口指针
            qDebug()<<"开始跳转";
            w->show();//跳转到mainpage窗口
            qDebug()<<"跳转成功";
            //this->myDatabase.quitConnection();//测试
        }
        else
        {
            qDebug()<<"登录失败！";
            ui->label_5->setText("登录失败！请重新输入");
        }
    }
}

