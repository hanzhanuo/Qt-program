#ifndef MY_LABEL_H
#define MY_LABEL_H

#include <QLabel>

class My_label : public QLabel
        //这里只需要在创建的时候实现对于QLabel的手写继承，就可以直接构建为对QLabel的继承
{
public:
    //My_label();
    My_label(QLabel* parent=nullptr);
    ~My_label()=default;   //这里原本设置的是不写，其实不写也是完全可以的

    //void enterEvent(QMouseEvent* ev) override;  //我之前写错了原来是因为对于enterEvent的主题理解错了
    //enterEvent的主体原来是整个event而不是单纯的mouseEvent啊
    //所以一定一定要切记：对于enter和leave，都属于整个event的，而不属于mouseEvent的
    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent* event) override;

    void mouseMoveEvent(QMouseEvent *ev) override;

    void mousePressEvent(QMouseEvent *ev) override;

    void mouseReleaseEvent(QMouseEvent *ev) override;

    //event     因为所有事件都是和event有关，所以这里想知道都可以对什么内容进行重载，就直接打个event作为提示符即可
    //所以这种函数都需要写什么的思路也非常明确：就比如事件相关的就都写成event然后进行提示即可


    bool event(QEvent* ev) override;

    bool eventFilter(QObject* obj,QEvent* ev) override;


    //对于notify的重写和对于event的重写都是bool类型的，并且两者都是用来过滤更为具体的事件的行为的
};

#endif // MY_LABEL_H
