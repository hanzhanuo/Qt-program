#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
//因为此时定义了多个数据成员，所以就需要对于每个数据成员都进行初始化操作
//这个对于每个数据成员的初始化操作一定一定不能忘了，这就是我打通cpp和Qt之间的壁垒的方法
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_current_Input("0")
    , m_pending_Operator("0")
    , m_result(0.0)
    , m_Waiting_Operator_Flag(false)
{
    ui->setupUi(this);

    //因为员工管理系统中写了：可以通过先创建ConnectFunc来实现对于每个connect函数的调用，然后再在构造函数中调用这个CF函数
    //感觉这样是更加成熟，更加增加代码可读性的写法
    ConnectFunc();
    //在这里调用CF函数，从而实现构造函数的代码量尽可能少。
    //所以以后写任何类似行为的函数，都可以封装在一个更大的函数当中，然后进行调用，这样能最大程度减少每个函数的代码量，增强解耦性


    ui->ResEdit->setText("0");   //这里表示的是在显示框里初始化显示为0
}

Widget::~Widget()
{
    delete ui;    //这个是所有的有ui的项目都有的内容，所以这个完全不用纠结，更不用自己写
}


//对于所有槽函数的实现
void Widget::When_Digit_Clicked()
{
    QPushButton* clicked_Button=qobject_cast<QPushButton*>(sender());
    //看来这个是必须要进行强转操作才能返回到这个QPushButton*指针了。
    //其他的注释内容都写在老师的代码的注释中了

    QString digit=clicked_Button->text();
    //其实上面这两步不是必须要写在一起的，即两行代码毫无关系，完全解耦
    //第一行代码的效果只是返回到底是哪个按键被选中了，
    //所以这个第一行代码和findChild的找某个固定类型的按钮，这两者的操作目的是完全一模一样的，只不过操作的途径不同而已


    //第二行代码只是对于拿到的QPushButton*进行的操作，所以理论上这里的第二行代码可以做各种操作


    if(m_Waiting_Operator_Flag==true){   //我个人比较蠢，所以最好还是按这个写法写，这样有助于自己理解代码

        m_current_Input=digit;
        //这就是原本没数字的时候，直接把数字缓冲区使用输入的数据进行覆盖的操作

        m_Waiting_Operator_Flag=false;   //表示此时已经有数字了

    }else{   //m_Waiting_Operator_Flag==false

        m_current_Input+=digit;   //如果有数字了，就进行追加输入

        //这个追加输入我是真没想到，所以这种一定就是边写边进行优化才能想到的处理方法

    }

    ui->ResEdit->setText(m_current_Input);
    //每次都要记住要把结果展示出来，经常忘了结果展示操作
}

void Widget::When_Operator_Clicked()
{
    QPushButton* clickedButton=qobject_cast<QPushButton*>(sender());

    QString new_operator=clickedButton->text();
    //所以进行QString展示的代码是一模一样的，只不过名字由数字变成了运算符

    double operand=m_current_Input.toDouble();
    //这种对当前数据字符串转化为数据的方法，非常非常重要，写多少遍了我还是会忘。
    //所以一定要对这个点反复的记忆

    if(!m_pending_Operator.isEmpty()){  // 如果运算符缓冲区非空
        //运算符缓冲区的清空操作可以说只有等号会进行操作实现，
        //所以这里缓冲区非空就是意味着可能进行的是连续计算的问题
        //比如点了一个"+5+"，但是一直没点等号，这个if逻辑内部就要处理这个连加问题
        //即当每次点了运算符但是运算符缓冲区是非空的时候，就要先处理上一个运算符
        //并且这里还体现了——————当前的总计算结果和当前的屏幕展示结果并不是同一个(这也是边研究边产生的业务逻辑的思考)

        if(m_pending_Operator == "+")
        {
            m_result += operand;
        }
        else if(m_pending_Operator == "-")
        {
            m_result -= operand;
        }
        else if(m_pending_Operator == "*")
        {
            m_result *= operand;
        }
        else if(m_pending_Operator == "/")
        {
            if (operand != 0.0)
            {
                m_result /= operand;
            } else
            {
                ui->ResEdit->setText("Error");
                m_pending_Operator.clear();
                return;
            }
        }
        //至此走完了所有运算符的逻辑，然后下面就是结果展示逻辑了

        m_current_Input=QString::number(m_result);
        //所以这种当前输入的数字和当前运算结果的转换，是必要的
        //必要性体现在当前输入早晚要承接结果并作为前操作数进一步进行运算的
        //这里的赋值操作是必要的，类型转换操作只是赋值操作的附属操作罢了

        m_pending_Operator.clear();   //这个是字符串清空的操作

        m_Waiting_Operator_Flag=true;





    }   //end of 运算符缓冲区非空
}

void Widget::When_Equal_Clicked()
{

}

void Widget::When_Clear_Clicked()
{

}

void Widget::ConnectFunc()
{

    //对于数字的connect函数
    for(size_t num=0;num<10;num++){

        QString ButtonName="ButtonNum"+QString::number(num);
        //这种写法一定要熟练，每次都必须要对于返回值快速获取

        QPushButton* digitButton=findChild<QPushButton*>(ButtonName);
        //findChild查找某个名字，就可以返回该特定部件的指针，
        //所以可以说这个是专门用来查找指针进行connect操作的函数

        connect(digitButton,&QPushButton::clicked,this,&Widget::When_Digit_Clicked);

        //connect(ui->B)
        //这里之所以不能使用ui->的方式直接实现第一个参数的调用，是因为此时在for循环内部，不能使用name进行指向操作，所以ui->的指向操作非常严格
        //所以可以进一步说：findchild使用的必要性只在for循环中

    }



    //对于加减乘除的connect函数
    connect(ui->addButton,&QPushButton::clicked,this,&Widget::When_Operator_Clicked);
    //这里之所以不能使用等号，是因为等号的代码逻辑和其他四个符号不同。
    //即其他四个符号的代码逻辑是完全相同的，才可以写在同一个槽函数中
    connect(ui->subButton,&QPushButton::clicked,this,&Widget::When_Operator_Clicked);
    connect(ui->mulButton,&QPushButton::clicked,this,&Widget::When_Operator_Clicked);
    connect(ui->divButton,&QPushButton::clicked,this,&Widget::When_Operator_Clicked);



    //对于等于号的connect函数
    connect(ui->eqlButton,&QPushButton::clicked,this,&Widget::When_Equal_Clicked);


    //对于清除的connect函数
    connect(ui->clearButton,&QPushButton::clicked,this,&Widget::When_Clear_Clicked);


}   //end of func ConnectFunc;



