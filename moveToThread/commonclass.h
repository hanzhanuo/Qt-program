#ifndef COMMONCLASS_H
#define COMMONCLASS_H

#include <QObject>
//每次创建新类的时候都要格外小心是需要继承的哪个类
//就比如想要使用widget的内容，但是却继承了dialog类，就会导致使用问题
//对于越往下的细分类的继承，就越容易导致继承出现错误
//所以在add new的时候创建类是个需要斟酌的操作，想要不出错就继承QObject

class CommonClass : public QObject
{
    Q_OBJECT
public:
    explicit CommonClass(QObject *parent = nullptr);


    void task1();   //声明需要进行操作的第一个任务
    void task2();   //需要操作的第二个任务


    //传统在普通类中是需要对run函数进行重写的，
    //但是这种方法就不需要进行重写，只需要通过moveto函数实现移花接木即可
    //但是思维量上会有些麻烦

signals:
    void QuitSingal();
    //信号只有声明和调用，没有具体的定义实现方法
    //并且这里要格外注意：当设置槽函数的时候，参数列表只能小于等于信号函数
    //所以每次在进行自定义槽函数的时候都需要注意先看信号函数都有什么参数，然后只能对对应的参数进行设置，不能自己瞎设置函数

};

#endif // COMMONCLASS_H
