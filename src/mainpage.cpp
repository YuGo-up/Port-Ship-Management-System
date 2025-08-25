#include "mainpage.h"
#include "ui_mainpage.h"
#include <QString>
#include "mainwindow.h"
#include "mainpage4.h"
mainpage::mainpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainpage)
{
    ui->setupUi(this);

    //连接数据库
    this->mydatabase.getconnection();
    //跳转提示
    qDebug()<<"跳转成功！";
    //为表格模式指针指定内存
    this->dataTableModle = new QStandardItemModel();
/*    //设置表格
    this->setTableInfo();
*/
    ui->controlpage->setCurrentIndex(3);//设置刚开始在空白页
}

mainpage::~mainpage()
{
    delete ui;
}

void mainpage::setTableInfo()
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
    ui->portTable->setColumnWidth(0,100);//第一列给200字节宽度
    ui->portTable->setColumnWidth(1,100);//第二列给200字节宽度
    ui->portTable->setColumnWidth(2,100);//第三列给200字节宽度
    ui->portTable->setColumnWidth(3,100);//第四列给200字节宽度
    ui->portTable->setColumnWidth(4,100);//第五列给200字节宽度
    ui->portTable->setColumnWidth(5,100);//第六列给200字节宽度
    //设置表格只读属性
    ui->portTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
    //将设计好的表格模式装载到表格上
    ui->portTable->setModel(this->dataTableModle);
}

void mainpage::getDatabaseInfo()
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

//跳到增加位
void mainpage::on_zeng_clicked()
{
    ui->controlpage->setCurrentIndex(0);//到第0页

    //切换模式清空之前的输入
    ui->shipID->clear();
    ui->shipname->clear();
    ui->shipdraft->clear();
    ui->intime->clear();
    ui->outtime->clear();
    ui->route->clear();
    ui->searchname->clear();

    //为表格模式指针指定内存
 //   this->dataTableModle = new QStandardItemModel();
    //设置表格
    this->setTableInfo();

}

//按下创建增加船舶信息
void mainpage::on_pushButton_clicked()
{
    QString nameid = ui->shipID->text();//用户增加进来的职工ID
    QString name = ui->shipname->text();//用户增加进来的职工姓名
    QString age = ui->shipdraft->text();//用户增加进来的年龄
    QString gender = ui->intime->text();//用户增加进来的性别
    QString posts = ui->outtime->text();//用户增加进来的职位
    QString route = ui->route->text();//用户增加的航线
    //检查用户输入
    qDebug()<<nameid;
    qDebug()<<name;
    qDebug()<<age;
    qDebug()<<gender;
    qDebug()<<posts;
    qDebug()<<route;
    if (name == "" ||nameid=="" ||age=="" ||gender=="" ||posts==""||route =="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->label_18->clear();
        ui->label_18->setText("不能为空请重新输入!");
        ui->shipID->clear();
        ui->shipname->clear();
        ui->shipdraft->clear();
        ui->intime->clear();
        ui->outtime->clear();
        ui->route->clear();

    }
    else
    {
    QSqlQuery sql;
    sql.prepare("insert into ships (shipID,sname,draft,intime,outtime,route) values(:nameid,:name,:age,:gender,:posts,:route)");
    sql.bindValue(":nameid",nameid);
    sql.bindValue(":name",name);
    sql.bindValue(":age",age);
    sql.bindValue(":gender",gender);
    sql.bindValue(":posts",posts);
    sql.bindValue(":route",route);

    bool addif = sql.exec();
    if(addif)
    {
        qDebug()<<"增加船舶成功！";
        ui->label_18->clear();
        ui->label_18->setText("增加船舶成功");
        mainpage::getDatabaseInfo();//重新获取信息并显示
        ui->shipID->clear();
        ui->shipname->clear();
        ui->shipdraft->clear();
        ui->intime->clear();
        ui->outtime->clear();
        ui->route->clear();

    }
    else
    {
        qDebug()<<"已有船舶编号，增加失败！";
        ui->label_18->clear();
        ui->label_18->setText("已有船舶编号，增加失败！");
        ui->shipID->clear();
        ui->shipname->clear();
        ui->shipdraft->clear();
        ui->intime->clear();
        ui->outtime->clear();
        ui->route->clear();

    }
    sql.clear();
    }
}
/*
//跳到增加位
void mainpage::on_zeng_clicked()
{
    ui->controlpage->setCurrentIndex(0);//到第0页
}
*/
//跳到修改页
void mainpage::on_gai_clicked()
{
    ui->controlpage->setCurrentIndex(1);//转到第1页

    //切换模式清空之前的输入
    ui->xshipID->clear();
    ui->xshipname->clear();
    ui->xdraft->clear();
    ui->xintime->clear();
    ui->xouttime->clear();
    ui->xroute->clear();
    ui->searchname->clear();

    //为表格模式指针指定内存
 //   this->dataTableModle = new QStandardItemModel();
    //设置表格
    this->setTableInfo();
}

//按下修改修改职工信息
void mainpage::on_pushButton_2_clicked()
{
    QString nameid = ui->xshipID->text();//用户修改进来的职工ID
    QString name = ui->xshipname->text();//用户修改进来的职工姓名
    QString age = ui->xdraft->text();//用户修改进来的年龄
    QString gender = ui->xintime->text();//用户修改进来的性别
    QString posts = ui->xouttime->text();//用户修改进来的职位
    QString route = ui->xroute->text();
    //检查用户输入
    qDebug()<<nameid;
    qDebug()<<name;
    qDebug()<<age;
    qDebug()<<gender;
    qDebug()<<posts;
    qDebug()<<route;
    //QSqlQuery sql;
    if (name == "" ||nameid=="" ||age=="" ||gender=="" ||posts==""||route=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->label_18->clear();
        ui->label_18->setText("不能为空请重新输入！");
        ui->xshipID->clear();
        ui->xshipname->clear();
        ui->xdraft->clear();
        ui->xintime->clear();
        ui->xouttime->clear();
        ui->xroute->clear();
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM ships where shipID=:userInputNumbe;");//从数据库中ships表找shipID = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",nameid);//:userInputNumber为用户输入的船舶编号
        sql.exec();//执行以上SQL语句
        QString a;
        while(sql.next())
        {
            a = sql.value("shipID").toString();
        }
        qDebug()<<"数据库找到的船舶编号"+a;//如果有就输出
        sql.clear();
        if(a == nameid)
        {
            qDebug()<<"找到";
            sql.prepare("update ships set sname=:name ,draft=:age ,intime=:gender ,outtime=:posts,route=:route where shipID= :nameid");
            sql.bindValue(":nameid",nameid);
            sql.bindValue(":name",name);
            sql.bindValue(":age",age);
            sql.bindValue(":gender",gender);
            sql.bindValue(":posts",posts);
            sql.bindValue(":route",route);

            bool addif = sql.exec();
            if(addif)
            {
                qDebug()<<"修改船舶信息成功！";
                ui->label_18->clear();
                ui->label_18->setText("修改船舶信息成功！");
                mainpage::getDatabaseInfo();//重新获取信息并显示
                ui->xshipID->clear();
                ui->xshipname->clear();
                ui->xdraft->clear();
                ui->xintime->clear();
                ui->xouttime->clear();
                ui->xroute->clear();
            }
        }
        else
        {
            qDebug()<<"输入的船舶编号不存在，修改失败！";
            ui->label_18->clear();
            ui->label_18->setText("输入的船舶编号不存在，修改失败！");
            ui->xshipID->clear();
            ui->xshipname->clear();
            ui->xdraft->clear();
            ui->xintime->clear();
            ui->xouttime->clear();
            ui->xroute->clear();
        }
    mainpage::getDatabaseInfo();//重新获取信息并显示
    sql.clear();
    }
}

//跳到删除页
void mainpage::on_shan_clicked()
{
    ui->controlpage->setCurrentIndex(2);//转到第2页

    ui->sshipID->clear();//用户修改进来的船舶编号
    ui->sshipname->clear();//用户修改进来的船舶名
    ui->searchname->clear();

    //为表格模式指针指定内存
 //   this->dataTableModle = new QStandardItemModel();
    //设置表格
    this->setTableInfo();
}

//删除函数
void mainpage::on_pushButton_3_clicked()
{

    QString nameid = ui->sshipID->text();//用户修改进来的船舶编号
    QString name = ui->sshipname->text();//用户修改进来的船舶名
    //检查用户输入
    qDebug()<<nameid;
    qDebug()<<name;
    if (name == "" ||nameid=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->sshipID->clear();//用户修改进来的船舶编号
        ui->sshipname->clear();//用户修改进来的船舶名
    }
    else
    {
    QSqlQuery sql;

        sql.prepare("SELECT * FROM ships where shipID=:userInputNumbe;");//从数据库中ships表找shipID = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",nameid);//:userInputNumber为用户输入的船舶编号
        sql.exec();//执行以上SQL语句
        QString a;
        QString b;
        while(sql.next())
        {
            a = sql.value("shipID").toString();
            b = sql.value("sname").toString();
        }
        qDebug()<<"数据库找到的船舶编号"+a;//如果有就输出
        qDebug()<<"数据库找到的船舶名"+b;//如果有就输出
        sql.clear();

        if(a == nameid && b == name)//如果用户输入的正确
        {
            qDebug()<<"找到";
            sql.prepare("delete from ships where shipID=:workerid and sname =:name");
            sql.bindValue(":workerid",nameid);
            sql.bindValue(":name",name);
            bool deleif = sql.exec();//执行以上SQL语句
            if(deleif)
            {
                qDebug()<<"删除成功";
                mainpage::getDatabaseInfo();//重新获取信息并显示
                ui->sshipID->clear();//用户修改进来的船舶编号
                ui->sshipname->clear();//用户修改进来的船舶名
            }
        }
        else
        {
            qDebug()<<"匹配失败，请重新输入！";
            qDebug()<<"删除失败，输入信息有误！";
            ui->sshipID->clear();//用户修改进来的船舶编号
            ui->sshipname->clear();//用户修改进来的船舶名
        }
        mainpage::getDatabaseInfo();//重新获取信息并显示
        sql.clear();
        }
        on_pushButton_4_clicked();
        on_shan_clicked();

    /*
    sql.prepare("delete from ships where shipID=:workerid and sname =:name");
    sql.bindValue(":workerid",nameid);
    sql.bindValue(":name",name);
    bool deleif = sql.exec();//执行以上SQL语句
    if(deleif)
    {
        qDebug()<<"删除成功";
        mainpage::getDatabaseInfo();//重新获取信息并显示
        ui->sworkerid->clear();//用户修改进来的船舶编号
        ui->sname->clear();//用户修改进来的船舶名
    }
    else
    {
        qDebug()<<"删除失败，输入信息有误！";
        ui->sworkerid->clear();//用户修改进来的船舶编号
        ui->sname->clear();//用户修改进来的船舶名
    }
    */
}



//用船舶名进行查询
void mainpage::on_pushButton_4_clicked()
{
    //为表格模式指针指定内存
 //   this->dataTableModle = new QStandardItemModel();
    this->dataTableModle->clear();
    QString searchname = ui->searchname->text();
    qDebug()<<searchname;
    if(searchname == "")
    {
        qDebug()<<"输入为空请重新输入！";
        ui->label_18->clear();
        ui->label_18->setText("输入为空请重新输入！");
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM ships where sname=:userInputNumbe;");//从数据库中ships表找shipID = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",searchname);//:userInputNumber为用户输入的船舶编号
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
            this->dataTableModle->setHorizontalHeaderItem(0,new QStandardItem("船舶编号"));
            this->dataTableModle->setHorizontalHeaderItem(1,new QStandardItem("船舶名"));
            this->dataTableModle->setHorizontalHeaderItem(2,new QStandardItem("排水量"));
            this->dataTableModle->setHorizontalHeaderItem(3,new QStandardItem("入港时间"));
            this->dataTableModle->setHorizontalHeaderItem(4,new QStandardItem("出港时间"));
            this->dataTableModle->setHorizontalHeaderItem(5,new QStandardItem("航线号"));
            //设置表格信息
            //从数据库中获取信息
            QSqlQuery sql1;
            //查询
            sql1.prepare("SELECT * FROM ships where sname=:userInput;");
            sql1.bindValue(":userInput",searchname);//:userInputNumber为用户输入的船舶编号
            sql1.exec();
            int row = 0;//定义变量表示表格行数
            while(sql1.next())
            {
                this->dataTableModle->setItem(row,0,new QStandardItem(sql1.value("shipID").toString()));//获取船舶ID并输出到第一列
                this->dataTableModle->setItem(row,1,new QStandardItem(sql1.value("sname").toString()));//获取船舶姓名并输出到第二列
                //qDebug()<<sql.value("pname");
                //qDebug()<<sql.value("pname").toString();
                this->dataTableModle->setItem(row,2,new QStandardItem(sql1.value("draft").toString()));//获取船舶排水量并输出到第三列
                this->dataTableModle->setItem(row,3,new QStandardItem(sql1.value("intime").toString()));//获取入港时间并输出到第四列
                this->dataTableModle->setItem(row,4,new QStandardItem(sql1.value("outtime").toString()));//获取出港时间并输出到第五列
                this->dataTableModle->setItem(row,5,new QStandardItem(sql1.value("route").toString()));//获取航线并输出到第六列
                row++;
            }
            sql1.clear();
            //设置列宽
            ui->portTable->setColumnWidth(0,100);//第一列给200字节宽度
            ui->portTable->setColumnWidth(1,100);//第二列给200字节宽度
            ui->portTable->setColumnWidth(2,100);//第三列给200字节宽度
            ui->portTable->setColumnWidth(3,100);//第四列给200字节宽度
            ui->portTable->setColumnWidth(4,100);//第五列给200字节宽度
            ui->portTable->setColumnWidth(5,100);//第六列给200字节宽度
            //设置表格只读属性
            ui->portTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
            //将设计好的表格模式装载到表格上
            ui->portTable->setModel(this->dataTableModle);
        }
        else
        {
            qDebug()<<"没有该船舶，请重新输入！";
            ui->label_18->clear();
            ui->label_18->setText("没有该船舶，请重新输入！");
            this->dataTableModle->clear();
            sql.clear();
        }

    }
}

//退出登录转到登录界面
void mainpage::on_pushButton_5_clicked()
{
    this->mydatabase.quitConnection();
    this->~mainpage();
    MainWindow * w = new MainWindow();
    w->show();
}

//转到职员信息操作界面
void mainpage::on_pushButton_6_clicked()
{
    /*
    //退出到登录界面
    this->mydatabase.quitConnection();
    this->~mainpage();
    MainWindow * w = new MainWindow();
    w->show();
    */
    //转到职员信息操作界面
    this->mydatabase.quitConnection();
    this->~mainpage();
    mainpage4 * w = new mainpage4();
    w->show();

}


void mainpage::on_count_clicked()
{

    //从数据库中获取信息
    QSqlQuery sql;
    sql.prepare("SELECT * FROM ships;");
    sql.exec();//执行以上SQL语句
    //----------获取结果集大小----------//

    if (sql.last())
    {

        qDebug()<<"结果集大小="<<sql.at() + 1;

    }

    int a = sql.at() + 1;
    QString ab = QString::number(a,10);  //十进制
    ui->summer->setText(ab);
    sql.clear();
}

