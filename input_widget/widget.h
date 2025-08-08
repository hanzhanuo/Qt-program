#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //对所有的输入部件进行练习，非常简单但是都必须要练一遍

    void Combo_box();  //下拉选择框，最好还能使用connect实现选择哪个就进行进一步的触发处理

    void Spin_box();   //旋转式微调框，用于实现一个一个数上升降低的

    void Time_Calender();

    void Slider();

    void Sequence_Edit();
};
#endif // WIDGET_H
