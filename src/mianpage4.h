#ifndef MIANPAGE4_H
#define MIANPAGE4_H

#include <QMainWindow>

namespace Ui {
class mianpage4;
}

class mianpage4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mianpage4(QWidget *parent = nullptr);
    ~mianpage4();

private:
    Ui::mianpage4 *ui;
};

#endif // MIANPAGE4_H
