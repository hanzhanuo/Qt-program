#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:    //无论是写为信号还是写为槽，都是要首先写上signals限定符

    void treat();    //信号都是只声明不定义的，槽才是既要声明又要定义
    //所以总结来说，就是槽比信号多了几步。

    void treat(QString name);
    //这里信号函数之所以跳转不到定义，是因为信号函数不需要也不允许有定义
    //所以只有除了信号函数之外的其他函数才允许有定义

};

#endif // TEACHER_H
