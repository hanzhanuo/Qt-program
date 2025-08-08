#include "timer.h"
#include "ui_timer.h"



Timer::Timer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timer)
{
    ui->setupUi(this);

    //就和事件过滤器一样，定时器的启动也是最好写在构造函数中的
    //然后根据查找知道startTimer的返回值是int类型的事件启动的启动器id，这个id是int类型的
    //并且这个返回值要全局使用，所以就优先想到设计为数据成员来实现
    //所以最终效果:
    m_id1=startTimer(500);
    m_id2=startTimer(1000);


    QTimer *tm = new QTimer(this);


    //这个信号槽必须创建在startTimer之前，这是因为信号槽本质上是一个函数调用操作
    //所以信号槽的调用和定时器的启动之间是有延时的。所以相比之下，事件就完全不存在延时的问题
    //这就是信号槽和事件之间的区别

    connect(tm, &QTimer::timeout, [=]{
        //所以可以看出：写QTimer类中的信号槽系统，使用的信号函数是timeout函数，
        //但是定时器仍然和重写timerevent没区别：仍然是在启动定时器startTimer的时候写下超时时间间隔
        //所以不管两种中的哪个方法，都绕不过使用startTimer来设置时间间隔(所以这个启动函数非常非常重要)

         static int num3 = 1;
         ui->label_3->setText(QString::number(num3++));
    });
    m_id3=startTimer(2000);
    //这个是通过设置方式2实现定时器操作:
    //方法就是通过创建类对象，然后对于对象进行信号槽实现定时器的代码逻辑


}

Timer::~Timer()
{
    delete ui;
}

void Timer::timerEvent(QTimerEvent *event)
//第一种定时器的启动方法就是对于时间启动器这个具体事件进行重写(所以就和对于鼠标的具体事件的重写是一模一样的操作)
//所以根据可迁移性，其实是也可以对event进行重写的。
{
    if(m_id1 == event->timerId())
        {
            static int num1 = 1;
            ui->label->setText(QString::number(num1++));
        }

        if(m_id2 == event->timerId())
        {
            static int num2 = 1;
            ui->label_2->setText(QString::number(num2++));
        }
}

