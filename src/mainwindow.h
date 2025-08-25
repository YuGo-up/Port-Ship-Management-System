#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Qwidget.h>
#include <QString>
#include <QDebug>
#include <database.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    database myDatabase;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void try_login();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
