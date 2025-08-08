#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>    //这就是对于表格部件的应用题，
//优先使用学习的表格部件的三种写法中的第二种写法，因为第二种写法更有助于进行位置修改

#include <QPushButton>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
