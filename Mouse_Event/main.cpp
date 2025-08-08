#include "mouse.h"

#include <QApplication>


//思路：分别使用三种方式进行重写，把所有重写方式都练一遍

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mouse w;
    w.show();
    return a.exec();
}
