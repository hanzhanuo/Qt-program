#include "paintevent.h"
#include "ui_paintevent.h"

#include <QPainter>

#include <QPainter>
//这种把某个实现文件中的思想，其实就是对于头文件可能会发生某个项目的重复调用所导致的重复定义的问题
//所以这种能少被调用一次(即不是必须要在全局使用的)就少调用一次的思想是以后在放置的时候二选一的时候非常重要的思想

PaintEvent::PaintEvent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PaintEvent)
{
    ui->setupUi(this);
}

PaintEvent::~PaintEvent()
{
    delete ui;
}

void PaintEvent::paintEvent(QPaintEvent *event)
//这里就是事件处理的五大方式中的重写某种特定事件的问题
//这里的特定问题就是想要实现三种矩形的绘制的代码逻辑，
//所以第一种和第二种的区别简直就是面向过程和面向对象之间的区别————即第一种暂时更符合人的逻辑，第二种是更高级的设计方法
{
   //因为这种事件类的都是只有一种细分，所以虽然有三种技术可以实现相同的重写逻辑，
   //但是这三种技术都是只能写在这一个函数中，不能写在别的函数中。所以三者只能通过注释进行区分
   //但其实总览：第三种方式是对于第二种方式的升级，所以综合来看第三种方式是最好用的方式，以后只需要记第三种方式即可


#if 0
    //方法1：画家不动，修改每次进行画画的位置
    QPainter paint(this);
    //对于继承和多态在Qt中应用的总结：
    //使用多态的时机就是在参数列表中需要传派生类的指针的时候，可以允许传基类的指针
    //使用继承的时机就是在调用函数的时候当基类有某个函数的时候，派生类基本都可以直接无脑使用(这就是Qt的特点)

    //因为这里的参数列表不是让传父对象生成对象树，所以这里就是单纯的传父类指针而已

    //QPen pen(QColor(Qt::green));   //不知道为什么这样写会报错，还是老实分步骤写吧
    QPen pen;
    pen.setColor(Qt::red);  //果然这样写就没问题

    pen.setBrush(Qt::Dense1Pattern);   //果然到处点完了之后，然后再进行上下翻就一定能翻到想要的内容

    paint.setPen(pen);

    QFont font;
    font.setBold(true);
    paint.setFont(font);
    //所以果然只要想查，什么内容都是可以查出来的————这个在那几道综合题中就有非常非常经典的体现

    paint.drawRect(10,10,200,200);
    //所以上述的所有代码，除了定义画笔以外，其他的都是在设置状态(颜色，字体，位置)。
    //只要是设置了的状态就都可以进行保存和调出。所以save可以理解为保存当前以上位置的所有状态

    pen.setColor(Qt::green);
    paint.setPen(pen);

    paint.drawRect(310, 10, 200, 100);

    //第三个矩形是红色
    pen.setColor(QColor(Qt::red));
    paint.setPen(pen);

    paint.drawRect(610, 10, 200, 100);
#endif



#if 0
    //方法2：直接修改画家的位置，不修改画画的起始位置了——————所以就是相对位移和绝对位移之间的关系
    //即此时每次draw的代码不用变动了，而是使用translate修改画家的位置
    //这种方法虽然没有简化代码量，也没有性能优势，但是这个方法是一种绘画事件中对于视角的转变，
    //是一种很好的转变思维，培养对象主体的判断思维的方法

    QPainter painter(this);
    //为了时刻保证在主体问题上的正确判断，这里作为画家类画家对象，就最好使用painter命名，而不是使用paint命名
    //所以这也是一个对于对象的命名规则的问题

    QPen pen;
    pen.setColor(QColor(Qt::red));
    painter.setPen(pen);

    painter.drawRect(10,10,200,100);


    painter.translate(300,0);
    //对于起始位置无需进行translate移动操作，只有对于后续的画家才需要进行移动操作
    //所以这就是移动的核心使用方法——————是先绘制再移动，而不是先移动再绘制

    pen.setColor(QColor(Qt::green));
    //所以有了移动之后，只不过是等价于进行修改的对象不同了，其余的无论代码量还是性能都没什么区别
    painter.setPen(pen);

    painter.drawRect(10,10,200,100);
#endif



//方法3：注意是对于画家的保存，所以只有画家的，并且是画家所有的状态内容就都会保存
//就比如这里对于画家设置了画笔，设置了位置，所以只对这些设置了的内容进行保存，没有设置的就不会保存
//然后就是restore的栈结构的恢复思想
//并且save一定是对于两次save之间的所有关于painter的状态的保存。所以这就是save的保存范围问题。
//然后还需要注意:当restore某个画家的状态快照的时候，就可以开始进行状态的修改了。
//所以无论是save之后还是restore之后，进行状态修改然后再save都是被允许的灵活操作





}

