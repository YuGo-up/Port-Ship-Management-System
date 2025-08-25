#include "mainwindow.h"
#include "database.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <mainpage.h>
#include <mainpage3.h>
#include <mainpage4.h>
//#include <mainpage2.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    database :: getconnection();
    //database :: quitConnection();
    MainWindow w;//登录窗口
    //mainpage w;//港口船舶窗口
    //mainpage3 w;//用户窗口
    //mainpage4 w;//港口职员窗口
    w.show();//显示窗口
    //database :: quitConnection();
    return a.exec();
    database :: quitConnection();
}
