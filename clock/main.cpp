#include "widget.h"

#include <QApplication>

//每次做作业的时候，都把它视作一个项目。那么对于项目永远不是先下手写，而是先进行架构设计和难点分析
//即先设计好架构，然后对架构中的每个点都进行分析，分析的时候想不到解决方案的就是自己的难点分析
//所以一定不要盲目写作业，要有设计的写
//即使对于已经讲过的有答案作业，也必须进行架构设计和难点分析，这就是写作业的设计思维的锻炼方法



/*
编程题：使用绘制事件完成钟表的绘制。
思路：这个题目比较细节，慢慢画

1、使用Qt绘图事件，肯定需要创建QPainter对象；

2、因为绘图设备是QWidget，所以需要重写paintEvent函数

3、代码实现过程中，QPainter有一个函数，rotate旋转函数，
该函数的作用是：顺时针旋转坐标系。给定的角度参数以度为单位。
函数原型是：void QPainter::rotate(qreal angle)

*/


/*
step1:问题分析：
时分秒三个针，设计每次转了一圈，就出发connect函数，然后对另一个针进行加多少angel的操作


step2：设计架构分析：
设计三个connect函数，然后设计一个按秒的定时器connect触发秒针转动


step3：难点分析
在没写的时候我暂时分析不出问题难点是什么

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
