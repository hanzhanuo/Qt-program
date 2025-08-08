#include "commonclass.h"

CommonClass::CommonClass(QObject *parent)
    : QObject(parent)
{
    //此时的构造函数中没有什么需要实现的内容，所以默认为空
}

//所以这个普通类中，只用来实现对于入口任务函数的函数逻辑的代码书写就可以了
//和线程有关的核心代码都是写在main函数中的——————这个无论是run方法还是moveto方法都是一样的
void CommonClass::task1()
{

}

void CommonClass::task2()
{

}
