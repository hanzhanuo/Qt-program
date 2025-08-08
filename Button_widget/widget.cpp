#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#include <QPushButton>
//之所以写在实现文件里，不写在头文件里，是因为头文件可能迁移到其他位置使用，
//而这个库只可能在实现文件中被使用到

#include <QToolButton>
#include <QRadioButton>
#include <QVBoxLayout>   //记住horizon是水平的地平线即可，剩下的都就被排除出来了
#include <QHBoxLayout>
#include <QCheckBox>
#include <QCommandLinkButton>   //尤其是这种一定要学会用首字母提示法，这是最高效的编代码方法
#include <QDesktopServices>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(600,480);
    //这是重置整个最基本单位部件画布的大小，所以论通用性最好就是写在其构造函数中
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Push_Botton()
{
    QPushButton* p_btn=new QPushButton(this);
    //普通按钮放上去就知道了，没法直接设置其名称。所以按钮类只能使用settext来实现设置名称
    //所以为了编代码规范性，最好紧跟着new对象写就好了
    p_btn->setText("按钮1");

    p_btn->resize(100,20);
    p_btn->move(100,100);

    p_btn->setFlat(false);    //这个是设计按钮的平整度，所以是flat不是flag

    connect(p_btn,&QPushButton::clicked,[p_btn](){
        //如果是获取this的话就是获取整个widget，如果是获取p_btn就能在函数体内操作pushbotton对象
        qDebug()<<p_btn->text();
        qDebug()<<p_btn->x()<<p_btn->y();

        QDesktopServices::openUrl(QUrl("www.baidu.com"));
        //所以意味着并不是只有链接按钮才可以出发链接跳转，只要是按钮都可以通过connect实现跳转
        //意味着以后记住：只要是需要单独挑出来库进行使用的东西，就一定是可迁移的，通用的东西
        //就比如这里的url和desktop，就都是在所有按钮中都可以使用的
    });


}

void Widget::Tool_Botton()
{
     QToolButton* p_tb=new QToolButton(this);
     p_tb->resize(200,40);
     p_tb->move(200,150);
     p_tb->setText("工具按钮");


     //工具按钮就和工具栏一模一样，都是可以设置图标和设置图标和文本布局

     //p_tb->setIcon("");
     p_tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     //这个设计布局的函数和在设计主窗口的时候的函数一模一样，但是前面的设计文本和图标的函数和前面是不同的
     //所以这个部件中的工具按键一定要和主窗口中的工具栏做好直接对比，这样记忆更高效


     //工具按钮同样也可以建立emit连接，
     //并且只要不是自定义的信号函数和槽函数，基本上都不需要手动进行emit(切记切记，非常非常重要)




}

void Widget::Radio_Botton()
{
    QRadioButton* p_rb1=new QRadioButton("单选按钮1",this);
    QRadioButton* p_rb2=new QRadioButton("单选按钮2",this);
    QRadioButton* p_rb3=new QRadioButton("单选按钮3",this);

    //和其他知识进行关联：和整个widget的布局进行关联
    QVBoxLayout* p_layout=new QVBoxLayout(this);
    p_layout->addWidget(p_rb1);
    p_layout->addWidget(p_rb2);
    p_layout->addWidget(p_rb3);

    setLayout(p_layout);   //对某些对象创建布局的三步走，一定一定要熟练


    connect(p_rb1,&QRadioButton::toggled,[p_rb1,p_rb2](){
        //所以捕获列表不需要写&符号，只需要逗号分隔即可
        qDebug()<<"单选1";
        p_rb1->move(100,300);
        p_rb2->move(200,400);
        //这里其实还可以进一步设置直接跳到超链接，所以还可以继续提升设计
    });

    //这种需要写三个connect函数，就充分体现了需要信号槽的一种局限性
    //—————即每次发送对象和接收对象只能有一个


    connect(p_rb2,&QRadioButton::toggled,[p_rb2](){
        qDebug()<<"单选2";
    });

    connect(p_rb3,&QRadioButton::toggled,[p_rb3](){
        qDebug()<<"单选3";

    });

}

void Widget::CheckBox_Botton()
{
    QCheckBox* p_cb1=new QCheckBox("复选按钮1",this);
    QCheckBox* p_cb2=new QCheckBox("复选按钮2",this);
    QCheckBox* p_cb3=new QCheckBox("复选按钮3",this);

    //这样就不用对每个按钮进行move了，
    //以后在只有单个按钮的情况下，就使用move;在多个按钮的情况下，就都使用布局方法
    QHBoxLayout* p_layout=new QHBoxLayout(this);
    p_layout->addWidget(p_cb1);
    p_layout->addWidget(p_cb2);
    p_layout->addWidget(p_cb3);
    setLayout(p_layout);


    p_cb1->setTristate(true);   //设置为三态模式：即选中，半选中，未选中
    p_cb1->setCheckState(Qt::Checked);   //使用默认的已经被选中的模式


    connect(p_cb1,&QCheckBox::stateChanged,[](int states){
        //这里的states表示枚举值,
        //因为这个信号函数是个有返回值的，所以才使用参数列表来获取信号函数传过来的参数


        switch(states){
           case Qt::Unchecked:{   //这里可以使用花括号，但是必须要加冒号，不允许没有冒号就使用case
            qDebug()<<"未选中状态";
           }

        case Qt::PartiallyChecked:{
            qDebug()<<"部分选中状态";
        }
      }

    });

}

void Widget::CommandLink_Botton()
{
    QCommandLinkButton* p_clb=new QCommandLinkButton("链接按钮",this);
    //总结为：只要是有test参数的，就不用使用setText设计参数；但是如果没有参数的就要紧接着这样手动设计

    p_clb->resize(200,250);
    p_clb->move(100,200);

    p_clb->setDescription("点击按钮跳转");
    //这个设置描述信息和获取描述信息是一对，就和设置文本和获取文本是一模一样的

    //并且这个设置描述信息是text的副文本，即text占主要位置，描述信息占副位置

    connect(p_clb,&QCommandLinkButton::clicked,[p_clb](){
        QDesktopServices::openUrl(QUrl("www.baidu.com"));
        //这里好像因为不是clb的库文件，所以不需要使用clb的指针进行调用，所以就不用捕获了
        所以还是需要对捕获进一步总结啊，主要就是需要总结什么时候需要使用指针进行调用？
    });

}

