#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "teacher.h"
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    //并且所有的connect都放在widget文件中，是因为它声明了Q_OBJECT宏，所以所有元对象系统都放在这里面是最好的
    //所以这个才是最最核心的需要写在widget中的原因

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void trigger_func();

private slots:
    void on_pushButton_clicked();
    void connect_func();

private:
    Ui::Widget *ui;
    Student* m_stu;
    Teacher* m_tc;
};
#endif // WIDGET_H
