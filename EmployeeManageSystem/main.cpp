#include "widget.h"

#include <QApplication>

/*
创建一个员工管理系统，包含：

1.一个QListWidget显示员工列表；
2.一个QLineEdit用于搜索员工 ；
3.添加/删除按钮 ；
4.实现搜索功能（实时过滤列表）；
5.使用信号槽连接界面交互

*/

/*

问题分析：
又是添加删除按钮，所以和前一天的对动态处理链表是完全一样的操作方法

如何通过实时过滤？这个就是对列表项的操作了，那么怎么实现对于列表项的操作？

各种界面交互我感觉基本上都是对于各种按钮的click和toggled
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
