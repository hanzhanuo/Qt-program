#include "filebroswer.h"
#include "ui_filebroswer.h"

FileBroswer::FileBroswer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileBroswer)
{
    ui->setupUi(this);
}

FileBroswer::~FileBroswer()
{
    delete ui;
}

void FileBroswer::setWidgetLayout()
//对于所有组件都设置布局的函数
//对所有组件设置布局的核心思路就是：必须要先整体后局部(先思考出整体布局，再一点点设计局部布局)，
//所以就和设计成员函数和信号槽函数的关系一模一样
{


    //有了上面的思路分析，这里就可以先整体后局部的写了(重写代码主要写的就是心路历程，所以一定要多写废话)
    //左侧目录树，右侧文件信息，然后两个大框之间使用splitter配合水平布局来实现

    //左侧：
    m_dirTree->setHeaderLabel("目录");

    //这里应该怎么设计还是要结合着老师给的常用函数一起看，这样就能起到学习复习的作用了




    //右侧：
}

void FileBroswer::setupConnections()
{

}

void FileBroswer::setupContextMenu()
{
    //这里设计一个QMenu类型的内容，就是为了进行addAction操作的，因为addAction是必须通过QMenu来承接其数据类型的，所以这里必须这样写


    //然后这里用了adAction中的先创建QAction对象，再添加到addAction中，所以这两个步骤一个都不能省，是必须这样写的
    QAction* action_Refresh=new QAction("刷新",this);
    m_treeMenu->addAction(action_Refresh);
    //先创建对象，再使用对象进行set，add操作基本上贯穿了整个Qt，
    //对于这些没别的办法，只能通过多练来实现——————一定要频繁练，频繁复习。对于我的学习方法优势就是频繁复习


    //这里写一个下拉子菜单就写一个connect，是个好习惯，以后我也这样写
    connect(action_Refresh,&QAction::triggered,this,&FileBroswer::refreshTree);
    //信号函数是种喇叭函数，但是槽函数并不是喇叭。是一个向上斜的E
    //并且可以通过图形和名字配合看出：信号函数和槽函数一个是普通时态，一个是过去时态，两者基本上都是有所对应的
    //然后官方槽函数和自定义槽函数都是向上斜的E

    //所以只要是指针类型，理论上都能作为connect的信号函数使用
    //并且经验来说，信号一定是过去式，只要不是过去式就要重新检查一遍是不是信号了

    //这里添加到tablemenu和treemenu的逻辑完全相同。
    //所以看来我已经完全复习好了对于一些菜单栏的架构该怎么设计了
    //所以这个尝试自己写

    QAction* action_Open=new QAction("打开",this);
    //所以写代码的重点就是知道自己下一步要干什么了+对基础知识点了解的非常透彻了。
    //我现在就属于这两者都没做到，所以导致我写起来像无头苍蝇一样

    //这行代码要是真正有思路，最好的方式应该是复制粘贴，而不是自己再凭记忆再写一遍
    QAction* action_Delete=new QAction("删除",this);

    m_tableMenu->addAction(action_Open);
    //使用的是action进行定义的变量，就一定是通过addAction函数进行实现。这种想法一定要极其熟练才可以
    m_tableMenu->addAction(action_Delete);

    //在写代码的时候一定要学会使用缩写和复制粘贴，这样写起来一定是最高效率的
    //(不过前提是必须要对思路和知识点非常非常熟练了才可以)


    connect(action_Open,&QAction::triggered,this,&FileBroswer::open_SelectFile);
    connect(action_Delete,&QAction::triggered,this,&FileBroswer::delete_SelectFile);
    //这两个connect的书写就体现出我connect思路上的薄弱了，主要薄弱在this指针的使用上


}



