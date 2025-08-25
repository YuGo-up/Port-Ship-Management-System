#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <Qwidget.h>
#include <QString>
#include <QDebug>
#include <database.h>
#include <QMainWindow>
#include <QStandardItemModel>
namespace Ui {
class mainpage;
}

class mainpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);
    ~mainpage();
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

    void on_zeng_clicked();

    void on_gai_clicked();

    void on_pushButton_2_clicked();

    void on_shan_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_count_clicked();

private:
    Ui::mainpage *ui;
};

#endif // MAINPAGE_H
