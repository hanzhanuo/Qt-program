#include "student.h"
#include <QDebug>   //包含这个头文件才能进行打印操作

//对于这种类的cpp来说，只是针对于头文件的实现文件，
//所以只需要进行实现，不需要写主程序的业务逻辑

Student::Student(QObject *parent) : QObject(parent)
{
    //构造函数的书写
}

void Student::eat()
{
    qDebug()<<"什么都不吃";
}

void Student::eat(QString name)
{
    qDebug()<<"老师请吃"<<name;
}




