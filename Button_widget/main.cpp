#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.Push_Botton();   //所以以后都用这种方法进行调用，不写在成员函数里了
    //并且作为进行设置的函数，所有用来设置的函数都必须放在show函数的前面，才能被显示出来，否则就没法显示(非常非常重要)
    w.Tool_Botton();
    w.Radio_Botton();

    w.show();
    //这个作为调用成员函数的方法，其实其他的成员函数也不是非要在构造函数中调用，直接写在这里像show函数一样调用即可


    return a.exec();

}
