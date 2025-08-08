#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QMenuBar>   //创建菜单栏所一定要包含的
#include <QPushButton>
#include <QToolBar>    //创建工具栏所一定要包含的
#include <QAction>
#include <QDockWidget>    //使用铆接组件必须要使用的头文件
#include <QStatusBar>   //果然让我猜对了，使用什么内容，头文件只需要多加一个Q即可

void MainWindow:: Menupart(){
    setWindowTitle("我的测试窗口");   //设置窗口的名称

    resize(100,200);
    //这里隐含了this指针，所以所有直接调用的函数基本上都是隐含this指针的
    //这也就意味着这个函数的作用四作用在当前类————mainwindow上的。这样就能快速分辨每个函数的作用域了

    //只有菜单栏有特殊的创建方法：menuBar，其他的都是直接使用new进行创建的
    //我的中心部件会把菜单栏遮挡住，应该就是因为我没常见这个菜单栏部件——————我真sb
    QMenuBar* p_bar=menuBar();
    setMenuBar(p_bar);

    QMenuBar* p_mb =new QMenuBar(this);
    //所以这种写法是完全错的，除了menu，其他部件都是new的，但是唯独唯独menu是不能用new的

    //但是在除了菜单栏以外，其他addMenu的位置都需要new QMenuBar对象


    /*
    这个表示的是整个菜单栏的单位，而不是具体每个菜单的单位。具体每个菜单是QMenu
    这里这个绑定this意味着整个菜单栏配合整个窗口的生命周期进行管理。
    所以之所以绝大部分的操作都写在这个最大的内容的构造函数内，就是因为把他们之间的对象树羁绊看作一个统一的整体
    所以以后要把Qt的比如这样的窗口作为一整个模块来看，这就是Qt和面向对象相类似的编程哲学
*/
    p_bar->resize(1000,400);

    QMenu* fileMenu=new QMenu("菜单",p_bar);
    //基于上面的整体模块理论，所以这里其实理论上也可以将每个菜单单元视作整个菜单栏的其中一个单位
    //因此这里其实也可以把生命书绑定到QMenuBar的指针上
    //但是规范来说都是绑定在this指针上，并且都是默认直接绑定的，所以根本不用写后面的这个指针参数了

     QMenu* editMenu=new QMenu("编辑",p_bar);
     QMenu* toolMenu=new QMenu("工具",p_bar);

     p_bar->addMenu(fileMenu);   //这里只需要传指针是因为上面已经传
     p_bar->addMenu(editMenu);
     p_bar->addMenu(toolMenu);
     //上下两种不同类型的指针，都可以使用addMenu函数，原因是继承。
     //所以只要是最大的父类能使用某个函数，后面的派生类都是默认可以使用这个函数的
     //并且上下两大组函数的最最主要区别就是：第二组是第一组的递归参数的递归调用，所以这就是
     fileMenu->addMenu("新建");
     fileMenu->addMenu("打开");
     fileMenu->addSeparator();      //添加分隔符的操作
     fileMenu->addMenu("保存");
     //Qt项目最重要就是要会复制粘贴，keil5也是如此。一定不要一点一点写，一定要会复制粘贴

     p_bar->move(100,0);




}   //end of funtion Menupart()



void MainWindow::Toolpart()
{
    QToolBar* p_tb=new QToolBar("工具栏");   //菜单的MenuBar就不能传字符串，原因是菜单位置是固定的，不需要解释是在干什么
    //addToolBar(p_tb);    所以我之前一直是忘写这个了，所以才导致没调用成功
    //所以这一步是调用的关键步骤
    //并且注意：这一步最好是直接写在创建p_tb指针的位置，这个是Menu所没有的步骤，所以没有对应性

    addToolBar(Qt::RightToolBarArea, p_tb);
    //前面加的这个参数1用于表示的工具栏此时初始化于什么位置，否则就会初始化出现在诡异的位置

    p_tb->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);   //限定菜单栏可能出现的位置
    //通过查索引可以看出来，这个的参数和addToolBar的限定位置的参数一模一样
    //并且这个参数严格只能是一个参数，所以想要使用就只能使用或符号来连接


    QToolBar*  p_tb2=new QToolBar("工具栏2");
    addToolBar(Qt::LeftToolBarArea,p_tb2);
    p_tb2->resize(100,20);
    p_tb2->addAction("工具栏2的内容");


    //p_tb->addAction("新建");
    //所以addAction和addMenu一样，既可以通过创建对象然后传对象指针，又可以通过直接传字符串来实现构建
    //两种构建方法效果是完全相同的

    //对整个工具栏的各种操作:两种等价的addAction的操作——————这种两种操作方式和addMenu的两种操作方式一模一样
    p_tb->addAction("获取工具");
    QAction* tool=new QAction("收藏工具");
    p_tb->addAction(tool);
    //这种传指针名和参数列表不同的原理：基类指针可以指向派生类对象

    //从最终体现的结果可以看出：这里的工具栏效果一定是不管设置多少个内容，都是出现在一整个工具栏模块中的
    //不会出现东一块西一块的效果

    p_tb->addSeparator();
    p_tb->addAction("再获取工具");
    QAction* temp=p_tb->addAction("再再获取工具");
    //temp->a("嵌套获取");
    //tool->addAction







} //end of function Toolpart()



void MainWindow::Centralpart()
{
    QPushButton* p_pb=new QPushButton("关闭窗口",this);
    p_pb->resize(200,100);
    p_pb->move(100,300);
    //这个表示以左上角为坐标原点，怎么进行移动(应该是所有的界面都可以这样位移)

    connect(p_pb,&QPushButton::clicked,[this](){    //所以this指针是可以捕获的，而参数列表只负责用于将信号的参数传递过来
        close();   //表示是this指针调用的，对于整个窗口的关闭，而不是对于某个菜单栏给关闭
        //所以对于一整个模块的直接操作，就是卸载这个模块里，并且频繁使用this指针的原因
    });


    //再设置一个按键为什么不行呢？    (非常非常重要的错误)
    //竟然真的是生命树的问题——————即所有的窗口设计都可以不传this指针，但是按键是千万千万不能缺this指针的
    QPushButton* p_pb2=new QPushButton("返回",this);
    p_pb2->resize(200,100);
    p_pb2->move(200,30);

    //p_pb2->setCentral   这样写当然是错的————应该是this指针为主题，进行中心的设置，肯定不能是按键为主体，设置中心组件

    connect(p_pb2,&QPushButton::clicked,[this](){    //所以this指针是可以捕获的，而参数列表只负责用于将信号的参数传递过来
        close();   //表示是this指针调用的，对于整个窗口的关闭，而不是对于某个菜单栏给关闭
        //所以对于一整个模块的直接操作，就是卸载这个模块里，并且频繁使用this指针的原因
    });

    //setCentralWidget
    //这个设计中心组件的方法为setter函数，意味着只可能创建一个中心组件，不可能同时设计两个中心组件的



    QPushButton* p_pb3=new QPushButton("核心组件按钮");
    p_pb3->resize(10,20);
    setCentralWidget(p_pb3);
    //添加中心部件总共就这两步，所以是所有模块中最最简单的操作了

}   //end of function Centralpart()


void MainWindow::Dockpart()
{
    QDockWidget* p_dock=new QDockWidget("浮动窗口");
    addDockWidget(Qt::LeftDockWidgetArea,p_dock);
    //第一个参数是必须要写的，不写函数就跑不通。
    //这个参数和设置滑动条的位置一模一样，都是需要单独设计出来的参数

}    //end of function Dockpart();


void MainWindow::Statuspart()
{
    QStatusBar* p_status=new QStatusBar();
    setStatusBar(p_status);

    QPushButton* p_btn1=new QPushButton("状态栏按钮1");
    QPushButton* p_btn2=new QPushButton("状态栏按钮2");

    p_status->addWidget(p_btn1);
    p_status->addPermanentWidget(p_btn2);   //这里表示的是设计一个永久的状态栏按键，默认放在左下角

    connect(p_btn1,&QPushButton::clicked,[this](){
        //所以一般来说lambda表达式仍然是逃不了写this指针的，只不过这里是把this指针写在捕获列表中了
        close();
    });
    //果然这个按钮仍然有关闭效果
    //——————所以只要是信号槽的对应内容，不管是放在任何模块的任何位置，都是始终有效的

}    //end of function Statuspart();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Menupart();
    Centralpart();
    Toolpart();
    Dockpart();
    Statuspart();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_widget_windowIconChanged(const QIcon &icon)
{

}
