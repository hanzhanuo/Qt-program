#include "widget.h"

#include <QApplication>


/*
创建一个文件目录浏览器，包含：

1.左侧QTreeWidget显示目录结构
2.右侧QTableWidget显示选中目录的文件详细信息
3.使用自定义数据模型
4.实现双击文件打开功能
5.添加右键菜单功能

*/


/*
问题分析：文件的详细信息，那如何实现选中的操作？

什么叫自定义数据类型

双击文件打开：是不是使用connect实现的？

如何是看点击右键打开一个内容？这个以前没学过啊

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
