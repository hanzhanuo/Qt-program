#include "widget.h"

#include <QApplication>

/*
使用ui进行界面设计，然后使用代码继续逻辑设计，计算器要有简单的+、-、*、/、=、清除等等功能。
（之前的作业里面已经设计过界面，现在只需要将代码逻辑写出来即可）

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
