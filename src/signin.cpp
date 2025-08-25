#include "signin.h"
#include "ui_signin.h"

signin::signin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signin)
{
    ui->setupUi(this);
}

signin::~signin()
{
    delete ui;
}
