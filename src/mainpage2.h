#ifndef MAINPAGE2_H
#define MAINPAGE2_H

#include <Qwidget.h>
#include <QString>
#include <QDebug>
#include <database.h>
#include <QMainWindow>
#include <QStandardItemModel>
namespace Ui {
class mainpage2;
}

class mainpage2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainpage2(QWidget *parent = nullptr);
    ~mainpage2();

private slots:
    void on_out_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mainpage2 *ui;
};

#endif // MAINPAGE2_H
