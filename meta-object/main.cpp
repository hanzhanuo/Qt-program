#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    Widget* w_ptr=new Widget(&w);     //这个就是把一个堆对象的生命绑定到一个栈对象上了
    Widget* w_ptr2=new Widget(w_ptr);   //所以这种通过指针的方法绑定对象树，仍然是个有效行为

    w.show();
    w_ptr->show();
    w_ptr2->show();
    return a.exec();
}
