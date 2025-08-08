#include "widget.h"
#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600,480);

    QListWidget* p_lw=new QListWidget(this);

    QPushButton* p_add=new QPushButton("Add Item",this);
    QPushButton* p_del=new QPushButton("Remove Selected",this);



    static int item_cnt=1;    //表示这里的初始的动态值为1，然后后面不断进行++更改
    //在lambda表达式中，想要进行引用捕获，就必须要小心引用的生命周期问题。所以这里就需要使用静态变量
    //静态数据成员和全局变量一样，都是甚至不需要进行捕获的，所以连引用捕获都省了

    connect(p_add,&QPushButton::clicked,[&](int x){
        //添加表项
        //p_lw->addItem(new QListWidgetItem());

        //这里想要实现添加动态改变的表项，唯一的办法就是使用字符串的转化和拼接操作(这两个操作极其极其重要，一定要非常熟练)

        p_lw->addItem("Item"+QString::number(item_cnt++));
        //这里有种助记方法：当使用的是把别的内容转换成字符串的时候，使用的就是to类型，
        //当是把字符串转换成别的内容的时候，就是直接作用于限定符+类型

    });

    connect(p_del,&QPushButton::clicked,[=](){
        //删除当前选中项
        //主要是要一边点击删除按钮，一边进行选中了，所以删除一定是对表项进行的删除


        //怎么体现这个当前选中了哪个呢？这个就要从listwidget的特性入手才能实现了
        //果然是使用listwidget的函数来实现的——————使用的listwidget的currentrow函数进行的实现
        p_lw->takeItem(p_lw->currentRow());

        //所以可以看出我的思路没问题，以后就按照思路，然后先查助手，查完助手还有问题就查ai。基本上问题就都解决了



        p_lw->deleteLater();
    });
}

Widget::~Widget()
{
}

