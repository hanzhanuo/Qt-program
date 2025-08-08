#ifndef PAINTEVENT_H
#define PAINTEVENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PaintEvent; }
QT_END_NAMESPACE

class PaintEvent : public QWidget
{
    Q_OBJECT

public:
    PaintEvent(QWidget *parent = nullptr);
    ~PaintEvent();

//    默认画画的方式就是进行重写paintEvent函数。
//    所以这个就像timerEvent一样，只要是某种事件想要实现某种代码逻辑，就必须要对该事件进行代码重写
//    即mouseEvent因为有各种各样的细分event，所以才没那么容易洞察出来。
//    实际上就应该理解为：paintEvent就是event下面的下属事件，这些下属事件有多少个早就一定固定了，但是其内部的代码逻辑没有被固定
//    所以重写这些细分的event函数，其实就是事件处理的五种方式中的其中一种。
//    然后再回想各种细分的mouseEvent是怎么进行重写的，就能理解这里重写的意义就是为了让这些事件发生的时候执行自己想要的代码逻辑，而不是默认的代码逻辑
//    所以这种重写的思维就和运算符重载的代码逻辑一样理解，就基本能想明白了
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::PaintEvent *ui;
};
#endif // PAINTEVENT_H
