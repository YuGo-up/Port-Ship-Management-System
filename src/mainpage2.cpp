#include "mainpage2.h"
#include "ui_mainpage2.h"
#include "mainwindow.h"
#include "mainpage.h"

mainpage2::mainpage2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainpage2)
{
    ui->setupUi(this);

}



void mainpage2::on_out_clicked()
{
    //this->mydatabase.quitConnection();
    this->~mainpage2();
    MainWindow * w = new MainWindow();
    w->show();
}


void mainpage2::on_pushButton_2_clicked()
{
    //this->mydatabase.quitConnection();
    this->~mainpage2();
    mainpage * w = new mainpage();
    w->show();
}

