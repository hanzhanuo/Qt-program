#include "myobject.h"

MyObject::MyObject(QObject *parent)
    : QObject(parent)
{

}

QString MyObject::getname() const
{
    return _name;
}

void MyObject::setname(const QString &name)   //这个是初始化设置名称的操作，下面才是重新设置名称的操作
{
    _name=name;
}



void MyObject::resetname(const QString &name)
//因为这个信号函数的含义是只有名字改变的时候才触发信号
//所以emit函数的效果就是什么时候导致函数信号触发，就可以把emit写在什么位置
//所以connect只是关联，emit才是触发
{
    if(_name!=name){
        _name=name;
        emit namechanged(name);    //这属于信号槽的高级用法：带条件的信号触发
        //emit的本质是函数调用，所以不要光写emit了，要知道emit的后面内容是什么

        //可以理解为clicked这个行为本身就是在信号触发了，所以才不需要特地设置emit函数
        //但是只要是像这里的自定义的信号函数的形式，就一定要通过条件去触发信号函数，然后再让信号函数触发槽函数
        //这就是写信号槽系统的除了connect函数外的另一套核心系统
    }
}


