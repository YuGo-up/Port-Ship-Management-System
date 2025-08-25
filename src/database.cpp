#include "database.h"
QSqlDatabase database :: db = QSqlDatabase :: addDatabase("QODBC");
QSqlQuery * database :: sql = NULL;
database::database()
{
    qDebug()<<"数据库实例已创建";
}
bool database :: getconnection()
{
    //数据库连接
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("1");
    db.setUserName("root");
    db.setPassword("guoyu20040802");
    if(!db.open())
    {
        qDebug()<<"连接数据库失败！";
        qDebug()<<db.lastError().text();
        return false;
    }
    else
    {
        qDebug()<<"成功连接数据库";
        return true;
    }
}
void database::quitConnection()
{
    //断开数据库连接
    qDebug()<<"断开数据库连接！";
    db.close();
}
