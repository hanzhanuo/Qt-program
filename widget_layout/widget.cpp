#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>    //在cpp中，库文件基本上都是没有.h的
#include <QHBoxLayout>
#include <QVBoxLayout>    //前面之所以写错，是因为忘记了一个原则:第一个字母永远是Q，然后后面才是对应的内容
#include <QGridLayout>
#include <QFormLayout>

#include <QLabel>    //使用布局中的标签内容，必须要先包含这个头文件
#include <QLineEdit>  //这个也是和label同理


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(600,500);
    GridLayout();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::HLayout()
{
    /*
    切记布局类型的函数就是三步走
    step1：创建所需要的布局对象
    step2：通过adder函数对对象进行添加
    step3：通过setter函数实现对添加进来的所有内容进行布局
    */

    //step1   创建堆对象
    QPushButton* p_btn1=new QPushButton("按钮1");
    QPushButton* p_btn2=new QPushButton("按钮2");
    QPushButton* p_btn3=new QPushButton("按钮3");
    QPushButton* p_btn4=new QPushButton("按钮4");

    //step2
    QHBoxLayout* p_hlayout=new QHBoxLayout();

    //这里和添加状态栏的添加部件一模一样，都是addWidget这种添加部件函数
    //一点改变都没有，所以可以理解为：只要是添加部件，必定就是addWidget的这两步来实现
    p_hlayout->addWidget(p_btn1);
    p_hlayout->addWidget(p_btn2);
    p_hlayout->addWidget(p_btn3);
    p_hlayout->addWidget(p_btn4);


    //step3
    this->setLayout(p_hlayout);
    //所以步骤3又是一次对于操作主体的挑战
    //——————即设置布局这个操作不是p_hlayout堆对象做的，而是widget这个this对象做的
    //这个只能记住，没有什么好反思的

}

void Widget::VLayout()
{
    //和水平排布完全一不一样，所以这个直接不写了
}

void Widget::GridLayout()
{
    //和单纯的水平垂直排布有区别，区别主要在在网格内进行偏移和进行填充的操作
    //再练一遍：
    QPushButton* p_btn1=new QPushButton("按钮1");
    QPushButton* p_btn2=new QPushButton("按钮2");
    QPushButton* p_btn3=new QPushButton("按钮3");
    QPushButton* p_btn4=new QPushButton("按钮4");

    QGridLayout* p_gl=new QGridLayout();

    //如果视为二维数组的话，二维数组的大小如何确定？
    //想起来了—————是前面必须要resize，然后通过resize来确定二维数组的大小，不能对二维数组越界
    p_gl->addWidget(p_btn1,100,100);
    p_gl->addWidget(p_btn2,1,2);
    p_gl->addWidget(p_btn3,4,6);
    p_gl->addWidget(p_btn4,1,20);
    //并且这种通过代码xie写出来的布局非常非常美观，直接就是等比例放缩
    p_btn2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //默认第一个是长，第二个是高
    //所以这个操作的含义就是长度上不变，高度上扩展

    setLayout(p_gl);

}

void Widget::FormLayout()
{
    //表格式的布局和其他三种都不一样，其代码行数最多
    //需要进行的处理逻辑也比三步走更多
    //如果让我总结，我就总结为：分别创建表格的键和值两类对象，
    //然后再对这两类对象进行addRow，之前的adder函数都是传一个参数，这个adder函数需要传键和值两个参数



        QLabel *name = new QLabel("姓名");
        QLabel *age = new QLabel("年龄");
        QLabel *sex = new QLabel("性别");

        QLineEdit *ledit1 = new QLineEdit;
        QLineEdit *ledit2 = new QLineEdit;
        QLineEdit *ledit3 = new QLineEdit;

        QFormLayout *fLayout = new QFormLayout;
        //fLayout->setRowWrapPolicy(QFormLayout::WrapAllRows );

        fLayout->addRow(name, ledit1);
        fLayout->addRow(age, ledit2);
        fLayout->addRow(sex, ledit3);

        setLayout(fLayout);
}

