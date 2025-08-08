#include "widget.h"

#include <QApplication>


/*
动态添加和删除列表项

要求：创建一个窗口，包含：
一个 QListWidget；
两个按钮 "Add Item" 和 "Remove Selected" ；
点击 "Add Item" 时，在列表末尾新增一项 "Item X"（X 是递增序号） ；
点击 "Remove Selected" 时，删除当前选中项

问题分析：主要问题就是如何对表项进行插入和删除操作，这个比较麻烦
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
