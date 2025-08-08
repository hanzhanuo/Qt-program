#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //所以基本上都是Main函数里面什么都不干，主要都写在这个类的实现文件中，这就是Qt设计的核心原则

    w.show();
    return a.exec();
}
