#include "widget.h"

#include <QDebug>
#include <QComboBox>
#include <QStringListModel>

#include <QSpinBox>

#include <QDateTimeEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QCalendarWidget>

#include <QKeySequenceEdit>

#include <QSlider>  //我自己写的时候又忘了加Q了，一定一定要注意头文件不要忘了加Q

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600,480);
}

Widget::~Widget()
{
}

void Widget::Combo_box()
{
    //依旧是创建，处理，设置属性，设置信号槽
    //这里的输入部件基本上都是这四步操作

    QComboBox* p_cb=new QComboBox(this);
    p_cb->resize(200, 30);
    p_cb->move(100, 20);

    QStringList city;
    city<<"北京"<<"上海"<<"重庆"<<"天津"<<"武汉";
    for(auto ele:city){
    //for(size_t ele=0;ele<5;ele++){
    //所以不是写法的问题，单纯是我哪个table越界了。那是什么原因导致越界了呢？
        p_cb->addItem(ele);
    }
    //和下面的轮盘转比较可以看出，只有这种需要重复进行编写来实现初始化的内容，才需要写for循环，
    //一步就能初始化成功的就不需要考虑for循环的操作

    p_cb->setCurrentIndex(3);   //设置默认显示哪个下标的内容

    connect(p_cb,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int idx){
        //一定要小心这种函数重载的形式，
        //主要要注意：唯一用来区分是使用的哪个重载形式的，就是设置尖括号内的参数来实现区分
        //并且一定要注意整个包括&符号都是放在of的括号内部的

        qDebug() << "idx = " << idx;
        qDebug() << "text = " <<p_cb->currentText();
    });

}   //end of func Combo_box；


void Widget::Spin_box()
{
    QSpinBox* p_sb=new QSpinBox(this);
    //这里的设置位置和大小，一定一定要习惯在创建出堆对象之后就立刻写上，养成习惯就可以少动脑了
    p_sb->move(100, 100);
    p_sb->resize(200, 30);

    p_sb->setRange(-100,100);
    p_sb->setValue(20);
    //在这个轮转方法中，设置默认值使用的是不是current，而是直接setter函数。这个需要格外注意

    p_sb->setSingleStep(10);   //设置每次进行修改的单位1

    connect(p_sb,QOverload<int>::of(&QSpinBox::valueChanged),[=](int x){
        //当使用重载形式的时候，那lambda表达式中就必须用写对应的参数了，
        //并且捕获列表因为可能会捕获多种内容，所以最优写法一定是写为整体捕获的方法

        qDebug() <<"x = " << x;
        qDebug() << "value = "<<p_sb->value();
        //有setter函数的形式就一定有非setter函数的形式，这两者一定是同时存在的
    });


}  //end of func Spin_box

void Widget::Time_Calender()
{
    QDateTimeEdit* p_dt=new QDateTimeEdit(QDateTime::currentDateTime(),this);
    //这三类堆对象的初始化非常非常特殊，都是通过静态成员函数进行初始化的
    //并且要注意：使用的还不是成员函数指针，而是成员函数。所以一定要格外注意，这里非常容易出错误


    QTimeEdit* p_te=new QTimeEdit(QTime::currentTime(),this);


    QDateEdit* p_de=new QDateEdit(QDate::currentDate(),this);
    //这里除了修改大小和移动操作以外，其他什么操作都做不了

    QCalendarWidget* p_cw=new QCalendarWidget(this);
    p_cw->resize(200,300);
    p_cw->move(100, 400);


    //connect(p_dt,&QDateTimeEdit::timeChanged|&QDateTimeEdit::dateChanged);
    //所以看来对于信号函数也是不能并排写在一个connect里，只能重复分别写在n个connect函数中

    connect(p_dt,&QDateTimeEdit::timeChanged,[](const QTime& time){
        //这里虽然没有函数重载，但是信号函数有参数列表。
        //只要是有参数列表的，就必须要承接。用不用是另一回事，但是必须要承接
        qDebug()<<"current time is "<<time.currentTime();
    });

    connect(p_dt,&QDateTimeEdit::dateChanged,[](const QDate& date){
        qDebug()<<"current day is "<<date.currentDate();
    });
}   //end of func Time_Calender;

void Widget::Slider()
{
    QSlider* p_Hsli=new QSlider(Qt::Horizontal,this);
    //切记滑动条和滚动条都是只用一种函数，是使用静态成员函数参数实现的横向和纵向的分别，
    //所以这一点上和时间日期问题非常类似
    QSlider* p_Vsli=new QSlider(Qt::Vertical,this);

    //针对垂直的和水平的滑动条，必须要设置不同的长和宽，以满足对应依附位置的特点
    //move函数在设置的时候也需要溜边设置，否则就会导致视图上非常难看

    p_Hsli->resize(200,10);
    p_Hsli->move(100,0);

    p_Vsli->resize(10,200);
    p_Vsli->move(0,200);


    //绝大多数情况下，只有下拉框，按钮这种东西才需要设置信号槽，其余内容基本上都没必要
    //所以这里就是完全不需要设置信号槽

}   //end of func Slider;

void Widget::Sequence_Edit()
{
  QKeySequenceEdit* p_kse=new QKeySequenceEdit(this);

  p_kse->resize(200,100);
  p_kse->move(100,200);

  connect(p_kse,&QKeySequenceEdit::keySequenceChanged,[=](const QKeySequence& ks){
      if(ks==QKeySequence("ctrl+v")){
          close();
      }
  });
}



