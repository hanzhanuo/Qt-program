#include "widget.h"
#include <QLabel>
#include <QMovie>
#include <QProgressBar>
#include <QLCDNumber>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600,480);   //这以后作为写每个项目都必写的内容
    setWindowTitle("展示部件");
}

Widget::~Widget()
{
}

void Widget::label()
{
    QLabel* p_label=new QLabel(this);
    p_label->move(100,30);
    p_label->resize(100,20);

    //label可以显示四大类内容：文本，静图，动图，html
    p_label->setFrameShape(QFrame::Box);
    //这里就是典型的作用于限定符来调用枚举值————所以不带括号就是枚举，带括号就是静态成员函数

    p_label->setText("文本标签");

    p_label->setPixmap(QPixmap::fromImage(QImage()));
    //所以这种方法和设置url的方法极其类似，都是一个括号叠着一个括号实现的
    //并且两种应该是都是参数是const类名&类型的，所以才会都使用静态成员函数的调用方法来实现
    //所以总结出一个规律：参数列表中要求填const类名引用的，都是需要写静态成员函数


    QMovie* p_movie=new QMovie(this);   //并且cpp中也是需要严格遵循前向声明顺序的，不能逆序进行内容的创建
    p_movie->setFileName();

    p_label->setMovie(p_movie);
    //这里参数列表中要求传一个Moovie类型的指针，就是需要创建堆对象了
    //所以这个参数和上面的setPixmap的参数刚好做鲜明对比，体现出不同参数列表第一时间应该想到传什么

    p_movie->start();   //最后还需要进行一步启动
    //所以动图的设置方法比静图复杂好多，主要愿意是需要创建堆对象，然后对堆对象进行配置；然后最后还需要一步启动操作
    //所以按这样记忆其实也能记个差不多

    设置超链接还没写




}    //end of func label

void Widget::LCD()
{
    QLCDNumber* p_lcd=new QLCDNumber(this);
    p_lcd->move(200,400);
    p_lcd->resize(100,20);

    //开始设置属性
    p_lcd->setSegmentStyle(QLCDNumber::Flat);

    p_lcd->setDigitCount(9);   //这个应该专门是为了设置数字相关的长度所设计的

    p_lcd->display("nihao");   //这里有三种参数：字符串，整数，小数
    //所以哪种都可以填，但是digit函数专门就是为了整数和小数设置的，对于字符串的展示没有效果
}

void Widget::Progress()
{
    QProgressBar* p_progress=new QProgressBar(this);

    p_progress->resize(200,20);
    //对于每个的大小的设置，都要注意是长条，竖条还是方块。这决定了能更高效率设计resize函数
    p_progress->move(400,20);

    p_progress->setOrientation(Qt::Vertical);
    //这个是设置进度条是横向的还是竖向的。好像所有的设置是横向还是竖向的方法都是使用这个函数，
    //所以这个函数在查找的时候，多个类中都有这个函数
    //因此以后只要搜索某个函数多个类中都有，那就最好每个类中的都看看，这样就能找到这种函数的共同点


    p_progress->setRange(0,100000);
    //之所以必须要设置大的数字，是因为for循环的处理速度非常非常快，所以够大才能看出变化

    p_progress->setValue(1000);
    //这两步和spinbox非常非常像，这就是上面说的：当某个函数在查找的时候有多个类的选项的时候，一定要一起看看，这些函数一定有共同点

    //这里在使用示例的时候，还进行了按钮和进度条的水平布局结构。
    //这个一定要熟练，以后这种布局结构有关的内容非常非常常用，要无脑就能写出来

}

