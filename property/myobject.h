#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QWidget>

class MyObject : public QObject
{
    Q_OBJECT   //继承和宏是必须同时存在的，所以两者出现基本上不会差一两行

    //Q_PROPERTY()
    //这个宏的第一个参数是type name。所以其属性的类型是自定义是什么类型的。
    //所以这里的时候的属性是QString，以及后面传的也是QString类型的字符串，都是因为一开始在定义宏的时候就定义为了字符串类型的
    Q_PROPERTY(QString name READ getname WRITE setname RESET resetname NOTIFY namechanged)
    //并且作为宏，写逗号是大忌，直接用空格分隔即可
    //并且这个宏的写法也是先整体后局部————即先设计宏，再设计函数声明，最后再管函数的实现
    //总共就五大参数，记熟练了就好了


private:
    QString _name;

public:
    explicit MyObject(QObject *parent = nullptr);   //构造函数的默认参数构造形式

    //写各种成员函数：其实成员函数的设计从c++最开始学的来说，也是可以确定只有几种类型的
    //getter，setter，reset。其中setter函数和reset函数一定都是对于某种资源的读操作，getter函数一定是对于某种资源的读操作

    //读操作一定是返回值为资源的类型，并且读操作的最后一定要加const
    QString getname()const;

    //写操作一定是参数列表是资源类型，返回类型一般是void形式。
    //所以刚好和读操作是完全相反的
    void setname(const QString& name);
    void resetname(const QString& name);



signals:
    //可以把这个视作和三种权限方式平级的方式了，只有当被视作信号函数还有槽函数的内容，才写在这个位置
    //槽函数需要多加一个slots关键字

    void namechanged(const QString& name);   //形参里参数名设计为什么都无所谓
    //并且作为信号函数，是只能声明不能定义的，一定不要忘了这个



    //是不是一个类中既可以定义信号函数，又可以定义槽函数？


};

#endif // MYOBJECT_H
