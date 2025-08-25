#include "mianpage4.h"
#include "ui_mianpage4.h"

mianpage4::mianpage4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mianpage4)
{
    ui->setupUi(this);
}

mianpage4::~mianpage4()
{
    delete ui;
}
