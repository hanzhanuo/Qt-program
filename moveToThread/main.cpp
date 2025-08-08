#include "widget.h"

#include "commonclass.h"

#include <QApplication>
#include <QThread>

#include <QObject>   //这个是用来实现在类外调用成员函数的

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    CommonClass* p_com=new CommonClass();
    QThread* p_qth=new QThread();
    p_com->moveToThread(p_qth);
    //这三步是传统方法中没有的，即创建普通类对象和线程类对象，然后普通类move到线程类的关联式方法
    //所以三步走的本质是对于普通和线程之间的关联操作


    //创建信号槽(信号槽在代码的哪个位置创建都可以，选择在这里是因为后面也没什么需要注意的东西了)
    //connect(p_qth,&QThread::started,p_com,&CommonClass::task1);
    //所以信号槽问题的关键点在于找到是哪个对象，而不是找到是哪个类的函数。因为只要确定了对象，就一定能确定对象是哪个类的，从而调用哪个类的函数
    //所以信号槽问题只要确定了信号对象和槽对象，剩下的就都不是问题

    //但是这里又有个问题：(就是为什么上面的connect函数报错了？)
    //原因就是之前一直是写在每个类中的，但是这里因为是在main函数中的，所以就只能通过类名+作用于限定符才能实现全局调用
    QObject::connect(p_qth,&QThread::started,p_com,&CommonClass::task1);
    QObject::connect(p_qth,&QThread::started,p_com,&CommonClass::task2);


    QObject::connect(p_com,&CommonClass::QuitSingal,);
    //如果这个是对于run的最终退出，那下面这个退出的connect的退出对象是谁？如果不写为lambda表达式形式应该怎么写？
    //分析：当没有使用this指针的时候，就说明不是类的，这里是main函数的，所以确实不是类的，所以感觉应该是connect的直接使用的main函数来操作的


    return a.exec();
    //return语句一定要是写在最后的位置的，不可能有代码写在return更往后的位置
    //所以才以return作为分界线，写中间的线程问题的
}
