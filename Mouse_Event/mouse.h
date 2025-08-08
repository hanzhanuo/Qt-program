#ifndef MOUSE_H
#define MOUSE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Mouse; }
QT_END_NAMESPACE

class Mouse : public QWidget
{
    Q_OBJECT

public:
    Mouse(QWidget *parent = nullptr);
    //这个指针是用来为继承所得来的基类进行初始化所以传入的参数
    //至于为什么要有基类就涉及到元对象系统了，所以必须要有这种基类

    ~Mouse();

private:
    Ui::Mouse *ui;
};
#endif // MOUSE_H
