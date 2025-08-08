#include "widget.h"
#include "myobject.h"

#include <QApplication>
#include <QDebug>


void test()
{
    MyObject obj;

    obj.setProperty("name","gzh");
    obj.property("name");
    //这就是键值对的构建和查找操作

    //这里不能写作成员函数，原因是需要创建MyObject对象，所以自然不能将定义写在MyObject类中

    QObject::connect(&obj,&MyObject::namechanged,[](const QString name){
        /*
        所以进一步证明了参数写在lambda表达式中的参数列表的位置，然后信号的参数会直接传递给槽函数
        并且这个一三变量的主体一定是发送者对象和接受者对象。如果两者像对象树一样属于同一个类，也不是不可能
        但是connect函数只起到绑定作用，不起到触发作用，触发作用仅与emit函数有关
        所以connect理论上写在哪都可以，最最常见的就是写在接受者的类中，从而直接使用this指针就行了。这个非常类似写成员函数的时候的rhs和lhs
*/

        qDebug()<<"name is changed to"<<name;
    });
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;


    w.show();
    return a.exec();
}
