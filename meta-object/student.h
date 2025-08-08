#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:


public slots:    //槽函数的声明位置前面必须要加这个关键字
    void eat();
    void eat(QString name);


    //信号函数和槽函数都是可以同时设计多个的，比如多个slots函数的效果都是emit另一个槽函数
    /*

    void saveDocument() {

    // 保存逻辑...

    emit saveStatusChanged(true);    //这个是用于使用一个槽函数触发另一个信号函数，从而造成连锁反应
    }

    void undo() {

    // 撤销逻辑...

    emit contentModified();
    }
*/

};

#endif // STUDENT_H
