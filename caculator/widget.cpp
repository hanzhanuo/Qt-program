#include "widget.h"
#include "ui_widget.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    resize(600,480);
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::calculator_view()
{
    //思路分析：设置一个单行文本框，设计4*4网状结构的按钮
    //按完按钮还必须要设置返回text文本，通过返回的文本进行计算操作

    QGridLayout* p_grid=new QGridLayout(this);

    QPushButton* p_add=new QPushButton("+");
    QPushButton* p_sub=new QPushButton("-");
    QPushButton* p_mul=new QPushButton("*");
    QPushButton* p_div=new QPushButton("/");
    QPushButton* p_eql=new QPushButton("=");
    QPushButton* p_rmv=new QPushButton("清除");

    //这里果然可以这样使用，那么尝试使用table视图实现这个操作
    //怎么写能写的代码最少最简便呢？  首先等间距4*4就是第一个问题
    //先固定每个的大小，再固定每个的位置。实现这两者应该就可以了
    p_grid->addWidget(new QPushButton("-"),1,2);


    //分析：首先要设置行和列的布局，然后才能把整个计算器实现出来

    //注意此时的connect是对于某个功能性按键进行操作的时候，才会触发，然后还需要有左右操作数
    connect(p_add,&QPushButton::clicked,[](){
        //如何找左操作数和右操作数？  是使用捕获还是参数列表？
        //就算是使用了捕获和参数列表，是不是应该使用text函数实现打印到输出区？
        //就算打印到了输出区效果又应该怎么进行计算，计算结果继续打印到输出区是吗？
    });


    connect(p_sub,&QPushButton::clicked,[](){

    });


}

void Widget::calculator_func()
{

}

