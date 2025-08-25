#include "mainpage3.h"
#include "ui_mainpage3.h"
#include <QString>
#include "mainwindow.h"
mainpage3::mainpage3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainpage3)
{
    ui->setupUi(this);

    //连接数据库
    this->mydatabase.getconnection();
    //跳转提示
    qDebug()<<"跳转成功！";
    //为表格模式指针指定内存
    this->dataTableModle = new QStandardItemModel();
    /*
    //设置表格
    this->setTableInfo();
    */
    ui->stackedWidget->setCurrentIndex(2);//设置刚开始在空白页
}

mainpage3::~mainpage3()
{
    delete ui;
}

/*

void mainpage3::setTableInfo()
{
    //设置表头
    this->dataTableModle->setHorizontalHeaderItem(0,new QStandardItem("船舶编号"));
    this->dataTableModle->setHorizontalHeaderItem(1,new QStandardItem("船舶名"));
    this->dataTableModle->setHorizontalHeaderItem(2,new QStandardItem("排水量"));
    this->dataTableModle->setHorizontalHeaderItem(3,new QStandardItem("入港时间"));
    this->dataTableModle->setHorizontalHeaderItem(4,new QStandardItem("出港时间"));
    this->dataTableModle->setHorizontalHeaderItem(5,new QStandardItem("航线号"));
    //设置表格信息
    this->getDatabaseInfo();
    //设置列宽
    ui->table->setColumnWidth(0,100);//第一列给200字节宽度
    ui->table->setColumnWidth(1,100);//第二列给200字节宽度
    ui->table->setColumnWidth(2,100);//第三列给200字节宽度
    ui->table->setColumnWidth(3,100);//第四列给200字节宽度
    ui->table->setColumnWidth(4,100);//第五列给200字节宽度
    ui->table->setColumnWidth(5,100);//第六列给200字节宽度
    //设置表格只读属性
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
    //将设计好的表格模式装载到表格上
    ui->table->setModel(this->dataTableModle);
}

void mainpage3::getDatabaseInfo()
{
    //从数据库中获取信息
    QSqlQuery sql;
    //查询
    sql.prepare("SELECT * FROM ships;");
    sql.exec();

    int row = 0;//定义变量表示表格行数
    while(sql.next())
    {
        this->dataTableModle->setItem(row,0,new QStandardItem(sql.value("shipID").toString()));//获取船舶ID并输出到第一列
        this->dataTableModle->setItem(row,1,new QStandardItem(sql.value("sname").toString()));//获取船舶姓名并输出到第二列
        //qDebug()<<sql.value("pname");
        //qDebug()<<sql.value("pname").toString();
        this->dataTableModle->setItem(row,2,new QStandardItem(sql.value("draft").toString()));//获取船舶排水量并输出到第三列
        this->dataTableModle->setItem(row,3,new QStandardItem(sql.value("intime").toString()));//获取入港时间并输出到第四列
        this->dataTableModle->setItem(row,4,new QStandardItem(sql.value("outtime").toString()));//获取出港时间并输出到第五列
        this->dataTableModle->setItem(row,5,new QStandardItem(sql.value("route").toString()));//获取航线并输出到第六列
        row++;
    }
    sql.clear();
}
*/
//查找船舶航线信息
void mainpage3::on_pushButton_clicked()
{
    this->dataTableModle->clear();
    QString searchname = ui->in->text();
    qDebug()<<searchname;
    if(searchname == "")
    {
        qDebug()<<"输入为空请重新输入！";
        ui->label_6->clear();
        ui->label_6->setText("输入为空，请重新输入！");
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM shipandroute where sname=:userInputNumbe;");//从数据库中ships表找sname = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",searchname);//:userInputNumber为用户输入的船舶名
        sql.exec();//执行以上SQL语句
        QString a;
        while(sql.next())
        {
            a = sql.value("sname").toString();
        }
        qDebug()<<"数据库找到的船舶编号"+a;//如果有就输出
        sql.clear();
        if(a == searchname)
        {
            //设置表头
            this->dataTableModle->setHorizontalHeaderItem(0,new QStandardItem("船舶名"));
            this->dataTableModle->setHorizontalHeaderItem(2,new QStandardItem("入港时间"));
            this->dataTableModle->setHorizontalHeaderItem(3,new QStandardItem("出港时间"));
            this->dataTableModle->setHorizontalHeaderItem(1,new QStandardItem("航线号"));
            //设置表格信息
            //从数据库中获取信息
            QSqlQuery sql1;
            //查询
            sql1.prepare("SELECT * FROM shipandroute where sname=:userInput;");
            sql1.bindValue(":userInput",searchname);//:userInputNumber为用户输入的船舶名
            sql1.exec();
            int row = 0;//定义变量表示表格行数
            while(sql1.next())
            {
                this->dataTableModle->setItem(row,0,new QStandardItem(sql1.value("sname").toString()));//获取船舶姓名并输出到第一列
                //qDebug()<<sql.value("pname");
                //qDebug()<<sql.value("pname").toString();
                this->dataTableModle->setItem(row,2,new QStandardItem(sql1.value("intime").toString()));//获取入港时间并输出到第三列
                this->dataTableModle->setItem(row,3,new QStandardItem(sql1.value("outtime").toString()));//获取出港时间并输出到第四列
                this->dataTableModle->setItem(row,1,new QStandardItem(sql1.value("route").toString()));//获取航线并输出到第二列
                row++;
            }
            sql1.clear();
            //设置列宽
            ui->table->setColumnWidth(0,100);//第一列给200字节宽度
            ui->table->setColumnWidth(1,100);//第二列给200字节宽度
            ui->table->setColumnWidth(2,100);//第三列给200字节宽度
            ui->table->setColumnWidth(3,100);//第四列给200字节宽度
            //设置表格只读属性
            ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
            //将设计好的表格模式装载到表格上
            ui->table->setModel(this->dataTableModle);
        }
        else
        {
            qDebug()<<"没有该船舶，请重新输入！";
            ui->label_6->clear();
            ui->label_6->setText("没有该船舶，请重新输入！");
            this->dataTableModle->clear();
            sql.clear();
        }
    }
}

//切换查找职员模式
void mainpage3::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);//到第0页
    this->dataTableModle->clear();
    //切换模式清空之前的输入
    ui->shipname->clear();
    ui->in->clear();

    //为表格模式指针指定内存
    //   this->dataTableModle = new QStandardItemModel();
    //设置表格
}

//查找职员信息
void mainpage3::on_pushButton_4_clicked()
{
    this->dataTableModle->clear();
    QString searchname = ui->shipname->text();
    qDebug()<<searchname;
    if(searchname == "")
    {
        qDebug()<<"输入为空请重新输入！";
        ui->label_6->clear();
        ui->label_6->setText("输入为空，请重新输入！");
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM worker where wname=:userInputNumbe;");//从数据库中worker表找wname = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",searchname);//:userInputNumber为用户输入的职工姓名
        sql.exec();//执行以上SQL语句
        QString a;
        while(sql.next())
        {
            a = sql.value("wname").toString();
        }
        qDebug()<<"数据库找到的职工姓名"+a;//如果有就输出
        sql.clear();
        if(a == searchname)
        {
            //设置表头
            this->dataTableModle->setHorizontalHeaderItem(0,new QStandardItem("职工姓名"));
            this->dataTableModle->setHorizontalHeaderItem(2,new QStandardItem("职工年龄"));
            this->dataTableModle->setHorizontalHeaderItem(1,new QStandardItem("职工性别"));
            //设置表格信息
            //从数据库中获取信息
            QSqlQuery sql1;
            //查询
            sql1.prepare("SELECT * FROM worker where wname=:userInput;");
            sql1.bindValue(":userInput",searchname);//:userInputNumber为用户输入的职工姓名
            sql1.exec();
            int row = 0;//定义变量表示表格行数
            while(sql1.next())
            {
                this->dataTableModle->setItem(row,0,new QStandardItem(sql1.value("wname").toString()));//获取职员姓名并输出到第一列
                //qDebug()<<sql.value("pname");
                //qDebug()<<sql.value("pname").toString();
                this->dataTableModle->setItem(row,2,new QStandardItem(sql1.value("wage").toString()));//获取职员年龄并输出到第三列
                this->dataTableModle->setItem(row,1,new QStandardItem(sql1.value("wgender").toString()));//获取职员性别并输出到第二列
                row++;
            }
            sql1.clear();
            //设置列宽
            ui->table->setColumnWidth(0,100);//第一列给200字节宽度
            ui->table->setColumnWidth(1,100);//第二列给200字节宽度
            ui->table->setColumnWidth(2,100);//第三列给200字节宽度
            //设置表格只读属性
            ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
            //将设计好的表格模式装载到表格上
            ui->table->setModel(this->dataTableModle);
        }
        else
        {
            qDebug()<<"没有该职工，请重新输入！";
            ui->label_6->clear();
            ui->label_6->setText("没有该职工，请重新输入！");
            this->dataTableModle->clear();
            sql.clear();
        }
    }
}


//切换查找船员信息模式
void mainpage3::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//到第1页
    this->dataTableModle->clear();
    //切换模式清空之前的输入
    ui->sname->clear();
    ui->cname->clear();
    ui->in->clear();

}

//查找船员信息
void mainpage3::on_pushButton_5_clicked()
{
    this->dataTableModle->clear();
    QString nameid = ui->sname->text();//用户修改进来的船舶名
    QString name = ui->cname->text();//用户修改进来的船员名
    //检查用户输入
    qDebug()<<nameid;
    qDebug()<<name;
    if (name == "" ||nameid=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->label_6->clear();
        ui->label_6->setText("输入为空，请重新输入！");
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM crewandship where cname=:userInputNumbe;");//从数据库中ships表找shipID = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",name);//:userInputNumber为用户输入的船员名
        sql.exec();//执行以上SQL语句
        QString a;
        QString b;
        while(sql.next())
        {
            a = sql.value("cname").toString();
            b = sql.value("cship").toString();
        }
        qDebug()<<"数据库找到的船员名"+a;//如果有就输出
        qDebug()<<"数据库找到的船舶名"+b;//如果有就输出
        sql.clear();

        if(a == name && b == nameid)//如果用户输入的正确
        {
            //设置表头
            this->dataTableModle->setHorizontalHeaderItem(0,new QStandardItem("船员姓名"));
            this->dataTableModle->setHorizontalHeaderItem(1,new QStandardItem("船舶名"));
            this->dataTableModle->setHorizontalHeaderItem(2,new QStandardItem("船员性别"));
            this->dataTableModle->setHorizontalHeaderItem(3,new QStandardItem("船员年龄"));
            this->dataTableModle->setHorizontalHeaderItem(4,new QStandardItem("职位"));
            //设置表格信息
            //从数据库中获取信息
            QSqlQuery sql1;
            //查询
            sql1.prepare("SELECT * FROM crewandship where cname=:userInput;");
            sql1.bindValue(":userInput",name);//:userInputNumber为用户输入的职工姓名
            sql1.exec();
            int row = 0;//定义变量表示表格行数
            while(sql1.next())
            {
                this->dataTableModle->setItem(row,0,new QStandardItem(sql1.value("cname").toString()));//获取船员姓名并输出到第一列
                //qDebug()<<sql.value("pname");
                //qDebug()<<sql.value("pname").toString();
                this->dataTableModle->setItem(row,1,new QStandardItem(sql1.value("cship").toString()));//获取船舶名并输出到第三列
                this->dataTableModle->setItem(row,2,new QStandardItem(sql1.value("cgender").toString()));//获取船员性别并输出到第一列
                this->dataTableModle->setItem(row,3,new QStandardItem(sql1.value("cage").toString()));//获取船员年龄并输出到第一列
                this->dataTableModle->setItem(row,4,new QStandardItem(sql1.value("cposts").toString()));//获取船员职位并输出到第一列
                row++;
            }
            sql1.clear();
            //设置列宽
            ui->table->setColumnWidth(0,100);//第一列给200字节宽度
            ui->table->setColumnWidth(1,100);//第二列给200字节宽度
            ui->table->setColumnWidth(2,100);//第三列给200字节宽度
            ui->table->setColumnWidth(3,100);//第三列给200字节宽度
            ui->table->setColumnWidth(4,100);//第三列给200字节宽度
            //设置表格只读属性
            ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
            //将设计好的表格模式装载到表格上
            ui->table->setModel(this->dataTableModle);
        }
        else
        {
            qDebug()<<"输入不匹配，请重新输入！";
            ui->label_6->clear();
            ui->label_6->setText("输入不匹配，请重新输入！");
            this->dataTableModle->clear();
            sql.clear();
        }
    }
}


void mainpage3::on_out_clicked()
{
    this->mydatabase.quitConnection();
    this->~mainpage3();
    MainWindow * w = new MainWindow();
    w->show();
}

