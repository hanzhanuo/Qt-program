#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void label();  //设置标签
    void LCD();    //设置液晶显示
    void Progress();   //设置进度条

};
#endif // WIDGET_H
