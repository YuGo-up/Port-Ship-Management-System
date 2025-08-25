#ifndef DATABASE_H
#define DATABASE_H
#include <QSql.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

class database
{
public:
    database();
    //数据库链接的相关函数
    static bool getconnection();//获得数据库链接
    static void quitConnection();//断开数据库链接
private:
    static QSqlDatabase db;//定义静态变量作为数据库链接实例
    static QSqlQuery *sql; //定义静态变量sql作为数据库执行语言实例
};

#endif // DATABASE_H
