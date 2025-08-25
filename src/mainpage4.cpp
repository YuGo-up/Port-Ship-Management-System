#include "mainpage.h"
#include "mainpage4.h"
#include "mainwindow.h"
#include "ui_mainpage4.h"
#include <QString>

mainpage4::mainpage4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainpage4)
{
    ui->setupUi(this);
    //连接数据库
    this->mydata.getconnection();
    //跳转提示
    qDebug()<<"跳转成功！";
    //为表格模式指针指定内存
    this->dataTableModle4 = new QStandardItemModel();
/*
    //设置表格
    this->setTableInfo4();
*/
    ui->workerstank->setCurrentIndex(3);//设置刚开始在空白页
}

void mainpage4::setTableInfo4()
{
    //设置表头
    this->dataTableModle4->setHorizontalHeaderItem(0,new QStandardItem("职员编号"));
    this->dataTableModle4->setHorizontalHeaderItem(1,new QStandardItem("职员姓名"));
    this->dataTableModle4->setHorizontalHeaderItem(2,new QStandardItem("职员年龄"));
    this->dataTableModle4->setHorizontalHeaderItem(3,new QStandardItem("职员性别"));
    this->dataTableModle4->setHorizontalHeaderItem(4,new QStandardItem("职位"));
    this->dataTableModle4->setHorizontalHeaderItem(5,new QStandardItem("联系方式"));
    //设置表格信息
    this->getDatabaseInfo4();
    //设置列宽
    ui->tableView->setColumnWidth(0,100);//第一列给200字节宽度
    ui->tableView->setColumnWidth(1,100);//第二列给200字节宽度
    ui->tableView->setColumnWidth(2,100);//第三列给200字节宽度
    ui->tableView->setColumnWidth(3,100);//第四列给200字节宽度
    ui->tableView->setColumnWidth(4,100);//第五列给200字节宽度
    ui->tableView->setColumnWidth(5,100);//第六列给200字节宽度
    //设置表格只读属性
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
    //将设计好的表格模式装载到表格上
    ui->tableView->setModel(this->dataTableModle4);
}

void mainpage4::getDatabaseInfo4()
{
    //从数据库中获取信息
    QSqlQuery sql;
    //查询
    sql.prepare("SELECT * FROM workers;");
    sql.exec();

    int row = 0;//定义变量表示表格行数
    while(sql.next())
    {
        this->dataTableModle4->setItem(row,0,new QStandardItem(sql.value("workerID").toString()));//获取船舶ID并输出到第一列
        this->dataTableModle4->setItem(row,1,new QStandardItem(sql.value("wname").toString()));//获取船舶姓名并输出到第二列
        //qDebug()<<sql.value("pname");
        //qDebug()<<sql.value("pname").toString();
        this->dataTableModle4->setItem(row,2,new QStandardItem(sql.value("wage").toString()));//获取船舶排水量并输出到第三列
        this->dataTableModle4->setItem(row,3,new QStandardItem(sql.value("wgender").toString()));//获取入港时间并输出到第四列
        this->dataTableModle4->setItem(row,4,new QStandardItem(sql.value("wposts").toString()));//获取出港时间并输出到第五列
        this->dataTableModle4->setItem(row,5,new QStandardItem(sql.value("wphone").toString()));//获取航线并输出到第六列
        row++;
    }
    sql.clear();
}


mainpage4::~mainpage4()
{
    delete ui;
}

//转到船员信息操作界面
void mainpage4::on_pushButton_clicked()
{
    /*
    this->mydata.quitConnection();
    this->~mainpage4();
    MainWindow * w = new MainWindow();
    w->show();
    */
    this->mydata.quitConnection();
    this->~mainpage4();
    mainpage * w = new mainpage();
    w->show();

}


//退出登录，转到登录界面
void mainpage4::on_out_clicked()
{
    this->~mainpage4();
    MainWindow * w = new MainWindow();
    w->show();
}

//查询职员信息
void mainpage4::on_searchworker_clicked()
{
    this->dataTableModle4->clear();
    QString searchname = ui->search->text();
    qDebug()<<searchname;
    if(searchname == "")
    {
        qDebug()<<"输入为空请重新输入！";
        ui->label_18->clear();
        ui->label_18->setText("输入为空，请重新输入！");
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM workers where wname=:userInputNumbe;");//从数据库中ships表找sname = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",searchname);//:userInputNumber为用户输入的职员名
        sql.exec();//执行以上SQL语句
        QString a;
        while(sql.next())
        {
            a = sql.value("wname").toString();
        }
        qDebug()<<"数据库找到的职员姓名"+a;//如果有就输出
        sql.clear();
        if(a == searchname)
        {
            //设置表头
            this->dataTableModle4->setHorizontalHeaderItem(0,new QStandardItem("职员编号"));
            this->dataTableModle4->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
            this->dataTableModle4->setHorizontalHeaderItem(2,new QStandardItem("年龄"));
            this->dataTableModle4->setHorizontalHeaderItem(3,new QStandardItem("性别"));
            this->dataTableModle4->setHorizontalHeaderItem(4,new QStandardItem("职位"));
            this->dataTableModle4->setHorizontalHeaderItem(5,new QStandardItem("联系方式"));
            //设置表格信息
            //从数据库中获取信息
            QSqlQuery sql1;
            //查询
            sql1.prepare("SELECT * FROM workers where wname=:userInput;");
            sql1.bindValue(":userInput",searchname);//:userInputNumber为用户输入的职员姓名
            sql1.exec();
            int row = 0;//定义变量表示表格行数
            while(sql1.next())
            {
                this->dataTableModle4->setItem(row,0,new QStandardItem(sql1.value("workerID").toString()));//获取职员编号并输出到第一列
                //qDebug()<<sql.value("pname");
                //qDebug()<<sql.value("pname").toString();
                this->dataTableModle4->setItem(row,1,new QStandardItem(sql1.value("wname").toString()));//获取职员姓名并输出到第二列
                this->dataTableModle4->setItem(row,2,new QStandardItem(sql1.value("wage").toString()));//获取职员年龄并输出到第三列
                this->dataTableModle4->setItem(row,3,new QStandardItem(sql1.value("wgender").toString()));//获取职员性别并输出到第四列
                this->dataTableModle4->setItem(row,4,new QStandardItem(sql1.value("wposts").toString()));//获取职位并输出到第五列
                this->dataTableModle4->setItem(row,5,new QStandardItem(sql1.value("wphone").toString()));//获取联系方式并输出到第六列
                row++;
            }
            sql1.clear();
            //设置列宽
            ui->tableView->setColumnWidth(0,100);//第一列给200字节宽度
            ui->tableView->setColumnWidth(1,100);//第二列给200字节宽度
            ui->tableView->setColumnWidth(2,100);//第三列给200字节宽度
            ui->tableView->setColumnWidth(3,100);//第四列给200字节宽度
            ui->tableView->setColumnWidth(4,100);//第五列给200字节宽度
            ui->tableView->setColumnWidth(5,100);//第六列给200字节宽度
            //设置表格只读属性
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读属性
            //将设计好的表格模式装载到表格上
            ui->tableView->setModel(this->dataTableModle4);
        }
        else
        {
            qDebug()<<"没有该职员，请重新输入！";
            ui->label_18->clear();
            ui->label_18->setText("没有该职员，请重新输入！");
            this->dataTableModle4->clear();
            sql.clear();
        }
    }
}


//转到增加职员模式
void mainpage4::on_add_clicked()
{
    ui->workerstank->setCurrentIndex(0);//到第0页

    //切换模式清空之前的输入
    ui->zID->clear();
    ui->zname->clear();
    ui->zage->clear();
    ui->zgender->clear();
    ui->zposts->clear();
    ui->zphone->clear();
    ui->search->clear();

    //为表格模式指针指定内存
    //   this->dataTableModle4 = new QStandardItemModel();
    //设置表格
    this->setTableInfo4();
}



//增加职员
void mainpage4::on_zengjia_clicked()
{
    QString nameid = ui->zID->text();//用户增加进来的职工ID
    QString name = ui->zname->text();//用户增加进来的职工姓名
    QString age = ui->zage->text();//用户增加进来的年龄
    QString gender = ui->zgender->text();//用户增加进来的性别
    QString posts = ui->zposts->text();//用户增加进来的职位
    QString route = ui->zphone->text();//用户增加的电话
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
        ui->label_18->setText("不能为空，请重新输入！");
        ui->zID->clear();
        ui->zname->clear();
        ui->zage->clear();
        ui->zgender->clear();
        ui->zposts->clear();
        ui->zphone->clear();

    }
    else
    {
        QSqlQuery sql;
        sql.prepare("insert into workers (workerID,wname,wage,wgender,wposts,wphone) values(:nameid,:name,:age,:gender,:posts,:route)");
        sql.bindValue(":nameid",nameid);
        sql.bindValue(":name",name);
        sql.bindValue(":age",age);
        sql.bindValue(":gender",gender);
        sql.bindValue(":posts",posts);
        sql.bindValue(":route",route);

        bool addif = sql.exec();
        if(addif)
        {
            qDebug()<<"增加职员成功！";
            mainpage4::getDatabaseInfo4();//重新获取信息并显示
            ui->label_18->clear();
            ui->label_18->setText("增加职员成功！");
            ui->zID->clear();
            ui->zname->clear();
            ui->zage->clear();
            ui->zgender->clear();
            ui->zposts->clear();
            ui->zphone->clear();

        }
        else
        {
            qDebug()<<"已有职员编号，增加失败！";
            ui->label_18->clear();
            ui->label_18->setText("已有职员编号，增加失败！");
            ui->zID->clear();
            ui->zname->clear();
            ui->zage->clear();
            ui->zgender->clear();
            ui->zposts->clear();
            ui->zphone->clear();

        }
        sql.clear();
    }
}


//转到修改职员信息模式
void mainpage4::on_update_clicked()
{
    ui->workerstank->setCurrentIndex(1);//转到第1页

    //切换模式清空之前的输入
    ui->xID->clear();
    ui->xname->clear();
    ui->xage->clear();
    ui->xgender->clear();
    ui->xposts->clear();
    ui->xphone->clear();
    ui->search->clear();

    //为表格模式指针指定内存
    //   this->dataTableModle = new QStandardItemModel();
    //设置表格
    this->setTableInfo4();
}



//修改职员信息
void mainpage4::on_xiugai_clicked()
{
    QString nameid = ui->xID->text();//用户修改进来的职工ID
    QString name = ui->xname->text();//用户修改进来的职工姓名
    QString age = ui->xage->text();//用户修改进来的年龄
    QString gender = ui->xgender->text();//用户修改进来的性别
    QString posts = ui->xposts->text();//用户修改进来的职位
    QString route = ui->xphone->text();//用户修改的联系方式
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
        ui->label_18->setText("不能为空，请重新输入！");
        ui->xID->clear();
        ui->xname->clear();
        ui->xage->clear();
        ui->xgender->clear();
        ui->xposts->clear();
        ui->xphone->clear();
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM workers where workerID=:userInputNumbe;");//从数据库中workers表找shipID = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",nameid);//:userInputNumber为用户输入的职员编号
        sql.exec();//执行以上SQL语句
        QString a;
        while(sql.next())
        {
            a = sql.value("workerID").toString();
        }
        qDebug()<<"数据库找到的职员编号"+a;//如果有就输出
        sql.clear();
        if(a == nameid)
        {
            qDebug()<<"找到";
            sql.prepare("update workers set wname=:name ,wage=:age ,wgender=:gender ,wposts=:posts,wphone=:route where workerID= :nameid");
            sql.bindValue(":nameid",nameid);
            sql.bindValue(":name",name);
            sql.bindValue(":age",age);
            sql.bindValue(":gender",gender);
            sql.bindValue(":posts",posts);
            sql.bindValue(":route",route);

            bool addif = sql.exec();
            if(addif)
            {
                qDebug()<<"修改职工信息成功！";
                ui->label_18->clear();
                ui->label_18->setText("修改职员信息成功！");
                mainpage4::getDatabaseInfo4();//重新获取信息并显示
                ui->xID->clear();
                ui->xname->clear();
                ui->xage->clear();
                ui->xgender->clear();
                ui->xposts->clear();
                ui->xphone->clear();
            }
        }
        else
        {
            qDebug()<<"输入的职员编号不存在，修改失败！";
            ui->label_18->clear();
            ui->label_18->setText("输入的职员编号不存在，修改失败！");
            ui->xID->clear();
            ui->xname->clear();
            ui->xage->clear();
            ui->xgender->clear();
            ui->xposts->clear();
            ui->xphone->clear();
        }
        mainpage4::getDatabaseInfo4();//重新获取信息并显示
        sql.clear();
    }
}



//跳转到删除模块
void mainpage4::on_delete_2_clicked()
{
    ui->workerstank->setCurrentIndex(2);//转到第2页
    //切换模式清空之前的输入
    ui->sID->clear();//用户要删的职员编号
    ui->sname->clear();//用户要删除的职员名
    ui->search->clear();

    //为表格模式指针指定内存
    //   this->dataTableModle = new QStandardItemModel();
    //设置表格
    this->setTableInfo4();
}



//删除职员
void mainpage4::on_shanchu_clicked()
{
    QString nameid = ui->sID->text();//用户修改进来的职员编号
    QString name = ui->sname->text();//用户修改进来的职员名
    //检查用户输入
    qDebug()<<nameid;
    qDebug()<<name;
    if (name == "" ||nameid=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->sID->clear();//用户修改进来的职员编号
        ui->sname->clear();//用户修改进来的职员名
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("SELECT * FROM workers where workerID=:userInputNumbe;");//从数据库中ships表找shipID = :userInputNumber的信息
        sql.bindValue(":userInputNumbe",nameid);//:userInputNumber为用户输入的职员编号
        sql.exec();//执行以上SQL语句
        QString a;
        QString b;
        while(sql.next())
        {
            a = sql.value("workerID").toString();
            b = sql.value("wname").toString();
        }
        qDebug()<<"数据库找到的职员编号"+a;//如果有就输出
        qDebug()<<"数据库找到的职员名"+b;//如果有就输出
        sql.clear();

        if(a == nameid && b == name)//如果用户输入的正确
        {
            qDebug()<<"找到";
            sql.prepare("delete from workers where workerID=:workerid and wname =:name");
            sql.bindValue(":workerid",nameid);
            sql.bindValue(":name",name);
            bool deleif = sql.exec();//执行以上SQL语句
            if(deleif)
            {
                qDebug()<<"删除成功";
                mainpage4::getDatabaseInfo4();//重新获取信息并显示
                ui->sID->clear();//用户修改进来的职员编号
                ui->sname->clear();//用户修改进来的职员名
            }
        }
        else
        {
            qDebug()<<"匹配失败，请重新输入！";
            qDebug()<<"删除失败，输入信息有误！";
            ui->sID->clear();//用户修改进来的职员编号
            ui->sname->clear();//用户修改进来的职员名
        }
        mainpage4::getDatabaseInfo4();//重新获取信息并显示
        sql.clear();
    }
    on_searchworker_clicked();
    //on_delete_2_clicked();
}


void mainpage4::on_pushButton_2_clicked()
{
    //从数据库中获取信息
    QSqlQuery sql;
    sql.prepare("SELECT * FROM workers;");
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

