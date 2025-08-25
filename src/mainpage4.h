#ifndef MAINPAGE4_H
#define MAINPAGE4_H

#include <Qwidget.h>
#include <QString>
#include <QDebug>
#include <database.h>
#include <QMainWindow>
#include <QStandardItemModel>
namespace Ui {
class mainpage4;
}

class mainpage4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainpage4(QWidget *parent = nullptr);
    ~mainpage4();
    //连接数据库的对象
    database mydata;

    //设置表格格式
    void setTableInfo4();

    //获取表格信息
    void getDatabaseInfo4();

    //表格组件模式
    QStandardItemModel * dataTableModle4;

private slots:
    void on_pushButton_clicked();

    void on_out_clicked();

    void on_searchworker_clicked();

    void on_add_clicked();

    void on_zengjia_clicked();

    void on_update_clicked();

    void on_xiugai_clicked();

    void on_delete_2_clicked();

    void on_shanchu_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mainpage4 *ui;
};

#endif // MAINPAGE4_H
