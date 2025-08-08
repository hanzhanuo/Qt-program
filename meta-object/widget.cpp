#include "widget.h"
#include "ui_widget.h"


//所有的connect函数都写在widget文件中，是因为这样更方便对所有的关系进行集中管理


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_stu=new Student();
    //这里严格就不能这样在构造函数里定义和实现，必须要使用在头文件中定义的方法
    //Teacher* m_tc=new Teacher();    这个的错法和上面是一样的

    m_tc=new Teacher();
    //注意：这里创建的一定一定是对象指针，然后指向堆对象，
    //以后对于所有的Qt都使用这种无脑写法

    connect_func();
    trigger_func();


}

Widget::~Widget()
{
    delete ui;
    delete m_stu;
    delete m_tc;
}

void Widget::trigger_func()
//就像多态一样，这里必须实现对于信号的调用，才是实现connect触发的最后一步
{
    //切记一定一定是对于信号函数的触发，对槽函数是完全不需要触发的
    emit m_tc->treat();
    emit m_tc->treat("黄焖鸡");
    //需要使用几种类型的重载函数形式，就把他们都触发出来
}


void Widget::on_pushButton_clicked()
{
    //等价于使用了connect函数，这个是ui版本的connect函数的写法

    close();   //所以在这个connect函数中，只需要写上对应的槽函数即可
    //所以这种只需要写槽函数的ui直接构造方法是必须要熟练掌握的connect方法
}

void Widget::connect_func()
{
    void(Teacher::*t_ptrVoid)()=&Teacher::treat;
    void(Teacher::*t_ptrArgs)(QString)=&Teacher::treat;
    //这两种写法证明了：使用指针指向的函数，只需要写函数名即可(因为函数名就是函数重载的唯一相同的标识)
    //然后真正用于辨别具体指向的是哪个重载形式的，其实是函数指针的返回值和参数列表
    //所以函数指针的写法惯例，就和new的写法惯例一样，都是先写出返回值和参数列表，然后再写具体的指针名


    void(Student::*s_ptrVoid)()=&Student::eat;
    void(Student::*s_ptrArgs)(QString)=&Student::eat;

    connect(ui->pushButton, &QPushButton::clicked,this,&Widget::close);
    connect(m_tc,t_ptrVoid,m_stu,s_ptrVoid);    //原来之前错是因为我写反了。。。太蠢了
    //所以这些指针和对象一定不能写反了位置，一定要严格一个对象和它对应的行为函数的指针绑定。这里写反位置出了好多错了

    connect(m_tc,t_ptrArgs,m_stu,s_ptrArgs);

    //lambda表达式的connect写法形式
    connect(m_tc,t_ptrArgs,[](QString name){    这里lambda表达式中的传参写在参数列表的位置是对的吗？;
        qDebug()<<"老师请吃"<<name;
    });

     //connect(m_tc,t_ptrVoid,m_stu,s_ptrArgs);
    //所以意味着，这里即使写错了参数对应个数也不会在写代码的时候报错的，所以这里是要自己小心排查的位置，不能靠编译器


    //函数重载的另外两种写法：这两种写法就类型等效为把函数指针直接写在参数列表中的写法
    connect(m_tc,QOverload<>::of(&Teacher::treat),
            m_stu,QOverload<>::of(&Student::eat));
    //这种写法没有c++14的写法好用，所以会用即可，以后常使用指针方法，lambda表达式方法，c++14这三种方法即可

    connect(m_tc,qOverload<>(&Teacher::treat),
            m_stu,qOverload<>(&Student::eat));     //并且两种写法都是如果要传参数，就传在尖括号中的写法

    connect(m_tc,qOverload<QString>(&Teacher::treat),
            m_stu,qOverload<QString>(&Student::eat));
    //所以这就是不同的函数重载的分辨方法————通过对尖括号中传不同的参数

}


