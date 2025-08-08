#include "EmployeeSystem.h"

#include <QApplication>


/*
题目：创建一个员工管理系统，包含：

一个QListWidget显示员工列表；

一个QLineEdit用于搜索员工

添加/删除按钮

实现搜索功能（实时过滤列表）；

使用信号槽连接界面交互
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EmployeeSystem system;
    system.show();

    return app.exec();
}
