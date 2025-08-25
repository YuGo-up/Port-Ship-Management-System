#ifndef MAINPAGE3_H
#define MAINPAGE3_H

#include <Qwidget.h>
#include <QString>
#include <QDebug>
#include <database.h>
#include <QMainWindow>
#include <QStandardItemModel>
namespace Ui {
class mainpage3;
}

class mainpage3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainpage3(QWidget *parent = nullptr);
    ~mainpage3();
    //连接数据库的对象
    database mydatabase;

    //设置表格格式
    void setTableInfo();

    //获取表格信息
    void getDatabaseInfo();

    //表格组件模式
    QStandardItemModel * dataTableModle;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_out_clicked();

private:
    Ui::mainpage3 *ui;
};

#endif // MAINPAGE3_H
