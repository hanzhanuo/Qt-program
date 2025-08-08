#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)

    , currentInput("")
    , pendingOperator("")
    //这两个操作表示初始化为空字符的操作，要学会这种空字符的初始化string的方法
    //因为毕竟之前学的都是初始化为strcpy的操作方法，所以这属于学新思路了

    , result(0.0)
    , waitingForOperand(false)
{
    ui->setupUi(this);  //对于ui的启动函数

    // 信号槽连接：数字按钮 0-9
    //这里看似只有一个connect，但其实是进行了10个数字的for循环connect。
    for (int i = 0; i < 10; ++i)
    {
        //UI按钮命名：Button0, Button1...   所以这里是根据ui设计后取的名字，所进行的字符串拼接操作
        QString buttonName = "Button" + QString::number(i);  //这一步好像是把数字转换成字符串的操作

        QPushButton *digitButton = findChild<QPushButton*>(buttonName);

        connect(digitButton, &QPushButton::clicked, this, &Calculator::onDigitClicked);
    }

    // 信号槽连接：运算符（+ - * /）ch
    //对于信号槽函数的使用this指针的分析：什么时候使用this指针，使用的是谁的this指针？
    //先说使用的是谁的：使用的是当前槽函数定义在谁的函数内部，就是谁的this指针;
    //什么时候使用this指针:只有当设计的槽函数是和当前的成员函数属于同一个类中的时候，才使用this指针。否则就是使用槽函数对应的对象来实现
    //所以从上面两行的总结来看,使用this指针的时机是比较少的，只有恰好需要触发这个类的行为的时候才会使用this指针
    //但是反过来说：触发当前类的行为又是非常非常常见的行为，所以使用this指针还是比较常见的
    connect(ui->ButtonPlus, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
    connect(ui->ButtonMinus, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
    connect(ui->ButtonMultiply, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
    connect(ui->ButtonDivide, &QPushButton::clicked, this, &Calculator::onOperatorClicked);

    // 信号槽连接：= 和 C
    connect(ui->ButtonEqual, &QPushButton::clicked, this, &Calculator::onEqualClicked);
    connect(ui->ButtonClear, &QPushButton::clicked, this, &Calculator::onClearClicked);

    ui->display->setText("0");  // 初始化显示 0


}    //end of 构造函数
//所以这里是直接在构造函数里面写了所有的connect函数。其实这里也可以把所有的connect写在一个connect_func函数中


Calculator::~Calculator()
{
    delete ui;   //这里就是对整个ui堆对象进行删除的操作
}




/*
下面的这些所有就都是设计槽函数了。所以只有声明才有先后，定义是没有先后之分的
一般来说在函数实现顺序上，都是先写构造函数，然后再写这些信号槽函数
并且从这里来看，信号槽函数如果是有通用的版本(即像这里这样)
*/

//数字按钮点击
void Calculator::onDigitClicked()
{
    //sender用于在槽函数内部获取触发当前槽执行的信号发送者对象
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    //qobject_cast是进行强转的函数
    //这里从效果上看就是：sender函数始终指的是信号的发送者，
    //从而实现了不管谁是信号的发送者，都可以使用clickedButton变量进行承接

    //至于为什么这里使用的是变量而不是数据成员，以及什么时候使用变量什么时候使用数据成员？
    //这些都是需要进一步归纳的问题————————我总结为：需要跨函数进行使用的，就不要设置为全局变量，而是需要设置为数据成员
    //所以由于这里是只需要在这个函数内进行使用的局部变量，所以就不需要设计为成员函数

    QString digit = clickedButton->text();

    /*
    这一步和下面的settext这两个步骤，是整个计算器操作的核心
    这里的含义就是：把信号发送者发送的内容接收过来

    一定要把text视作cout展示内容，setText就是cin输入内容。这种cin，cout的思想一定要熟练
    */

    if (waitingForOperand)   //等待操作数=true就表示还在等待新的操作数digit
        //这种bool类型的标志位，最好设计为isXXX，这样后续回看代码会更有可读性
    {
        currentInput = digit;
        //我之前一直有误区————即我之前一直在思考这里如果是运算符会怎么样。但其实这里根本不可能是运算符
        //这个变量之所以被叫做数字，是因为这个函数只可能被按下数字触发，所以用来承接sender的digit就一定是数字，不可能是运算符
        //而此时的等待运算符标志位作为数据成员等价于全局变量来看，在各个函数中都可以对这个量进行修改，才是这个量作用于全局区域的意义

        //所以这种槽函数的思想非常非常重要——————槽函数的思想能有效避免一些不必要的分类讨论。以后一定不能再因为这个进行无脑分类讨论这种傻事了
        waitingForOperand = false;
    }
    else   //=false的时候就表示此时不再等待新的操作数了
    {
        currentInput += digit;   //然后这里执行的是对于字符串的拼接
        //后面在进行运算符的点击操作的时候，才会进行字符串和数据的转换，
        //所以这里只是进行字符串的存储，而不是对字符串的数据转换处理
    }

    //setText始终是对当前的结果进行展示的操作(cout的效果)
    ui->display->setText(currentInput);
    //这里千万不能被多个箭头唬住，这里的ui->display其实等价于用代码写的一个堆对象
    //所以以后只要是ui->xxx，就把这个整体一律视作是一个堆对象即可
}

// 运算符（+ - * /）点击
void Calculator::onOperatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString newOperator = clickedButton->text();
    //由于前面分析过了sender函数的效果，所以无论是哪种按键，都是一定一定要无脑写这两步的
    //这两步既实现了承接按钮，又实现了对按钮的内容的承接。所以属于两个对于函数返回值的承接操作
    //正是有了这两步承接操作，才有了后面的操作

    //所以以后这两个承接操作可以作为槽函数的常用处理方法来使用。并且这就是text函数之于槽函数的重要之处

    // 把字符串转换为double类型的操作,这里的含义是把运算数转换为double类型
    //这里的操作是把当前的数据成员转化为局部变量进行使用，并且这里不是简单的转化，而是字符串和数值之间的转化
    double operand = currentInput.toDouble();

    if (!pendingOperator.isEmpty())   //这个if表示此时运算符非空，即表示此时是有运算符可以使用的

        //这里可以根据非空进行放心的处理，原因是等号会帮忙托底，把所有异常情况都解决掉，所以到这里的加减乘除运算符就可以放心进行计算了
        //并且这里的用局部变量承接数据成员的操作，一定一定要会，这个在Qt中进行问题处理有很大作用
    {

        //这里不能使用switch是因为swtich的变量的数据类型有严格限制，所以string类型理所当然的就会被限制了
        if (pendingOperator == "+")
        {
            result += operand;
        }
        else if (pendingOperator == "-")
        {
            result -= operand;
        }
        else if (pendingOperator == "*")
        {
            result *= operand;
        }
        else if (pendingOperator == "/")
        {
            if (operand != 0.0)
            {
                result /= operand;
            } else
            {
                ui->display->setText("Error");
                //又是一个ui->的问题，以后记住把ui->display整体看成一个栈对象即可
                return;
            }
        }
    }
    else   //表示此时运算符缓存中没有内容，那结果就仍然是当前的操作数没有进行修改
    {
        result = operand;   //当运算符没内容的时候，就是不进行修改，所以就是对当前的结果只进行赋值操作
    }

    pendingOperator = newOperator;
    //这一步是无论是否非空，代码逻辑都走完了。所以下面就是需要对运算符缓冲区进行更新了，更新为最新接收的缓冲区
    //所以其实这个函数的代码逻辑是这样的：
    //当触发加减乘除的时候，不是执行当前加减乘除，而是对之前的加减乘除进行处理，然后再把当前触发的运算符压栈保存，下一次再走运算符的时候就处理新压栈的这个
    //所以总结来说就是：触发一个运算符的时候，就把之前的运算符处理掉，并把现在触发的运算符压栈，然后等待下一次再来运算符的时候进行处理

    waitingForOperand = true;

    ui->display->setText(QString::number(result));
}

// 等于号 (=) 点击
void Calculator::onEqualClicked()   //此时唯一的区别就是不对按键的sender进行捕获和展示了，其余的操作完全相同
{
    if (!pendingOperator.isEmpty())   //仍然是运算符缓冲区非空，就对这个运算符缓冲区进行计算操作
    {
        double operand = currentInput.toDouble();

        // 执行最后的运算
        if(pendingOperator == "+")
        {
            result += operand;
        }
        else if(pendingOperator == "-")
        {
            result -= operand;
        }
        else if(pendingOperator == "*")
        {
            result *= operand;
        }
        else if(pendingOperator == "/")
        {
            if (operand != 0.0)
            {
                result /= operand;
            } else
            {
                ui->display->setText("Error");
                pendingOperator.clear();
                return;
            }
        }


        currentInput = QString::number(result);

        pendingOperator.clear();
        //这是和加减乘除的另一个区别：加减乘除是把运算符留在缓冲区，
        //等号是通过对运算符处理完毕之后，就把处理完成的运算符全部清空
        //所以每次走等号都一定是对运算符处理完成了的

        waitingForOperand = true;
        ui->display->setText(currentInput);
    }
}

//点击清除按钮
void Calculator::onClearClicked()
{
    currentInput = "0";
    pendingOperator.clear();
    result = 0.0;
    waitingForOperand = false;

    ui->display->setText(currentInput);
    //所以clear函数还需要把当前的输入值和当前的展示值一并设置为0
    //所以这个一并设置为0的操作一定要学会
}
