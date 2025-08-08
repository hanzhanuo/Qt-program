#include "widget.h"
#include "ui_widget.h"


#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(600,480);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::test()
{
    QListWidget* p_listwidget=new QListWidget(this);
    //这里让我感受到了：一定要具体区分好整个列表和每个单个列表项之间的区别

    //使用for循环来构建员工列表
    //设置列数和行数

    //p_listwidget


    QPushButton* p_add=new QPushButton("添加按钮",this);
    QPushButton* p_del=new QPushButton("删除按钮",this);
    //到最后直接对这些按钮进行布局即可，现在只需要进行设置大小操作
    p_add->resize(40,40);
    p_del->resize(40,40);


    //进行添加的信号槽
    connect(p_add,&QPushButton::clicked,[](QString info){
        QListWidgetItem* p_listItem=new QListWidgetItem(info);

        //这里如何具体体现员工的各种信息呢？ 我感觉还是要用捕获列表从外部捕获啊

    });

    //进行删除的信号槽
    connect(p_del,&QPushButton::clicked,[=](){

        p_listwidget->removeItemWidget();
        //这里要传入的参数是一个指针用指针实现删除对应的员工的操作
        //所以就要有选中的操作，当选中列表的某个项的时候，就返回一个指针，然后指针传入进行删除
        //我的思路是设置另一个connect的lambda表达式中用于接收这个指针，然后再把这个指针传入这个lambda表达式中


    });


    QLineEdit* p_linedit=new QLineEdit("搜索员工框",this);
    p_linedit->resize(200,40);    //一般来说只需要写大小就行，位置最好使用布局来实现
    p_linedit->setPlaceholderText("请输入要搜索的员工");

    //那么如何进一步实现搜索功能呢？  或者说想要实现什么样的搜索功能？
    //那肯定是填入list表项，然后返回对应的表项



    //那么如何实现上面的这个操作呢？——————我的思路当然是查找最合适的信号函数
    //所以我这里设置当编辑完成的时候就触发信号函数——————一定要养成自己查的习惯，Qt不要太依靠老师教，要学会自己查自己学
    connect(p_linedit,&QLineEdit::editingFinished,[](){
        //这里面要获取编辑了什么内容，然后对内容进行搜索才对

        //现在假设获取了编辑什么内容，那应该如何进一步搜索？

    });





}

