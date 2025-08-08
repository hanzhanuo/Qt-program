#include "widget.h"
#include "ui_widget.h"

#include <QTreeWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QFileDialog>

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


    //使用自定义的数据模型该如何实现？  什么叫自定义的数据模型？

    QTreeWidget* p_treewidget=new QTreeWidget(this);

    QTableWidget* p_tablewidget=new QTableWidget(this);
    //这里还有参数可以初始化行和列，但是为了保证自由度，就先等后面再进行初始化这个吧

    //如何设置最左侧和最右侧？   我暂时的思路还是设置网状布局，然后使他俩到最左侧和最右侧


    //进行文件信息调出的信号槽
    //table的效果应该是能随时切换显示的文件信息。因为是实时，所以应该是信号槽
    connect(p_treewidget,&QTreeWidget::itemClicked,[](){
        //这里面应该能实现显示被选中的内容的详细信息，
        //那这个详细信息被存到了哪，又是怎么被调出的呢？

        //p_tablewidget->
    });


    //如何实现双击打开文件？
    connect(p_treewidget,&QTreeWidget::itemDoubleClicked,[=](QTreeWidgetItem *item,int col){
        QString path=QFileDialog::getOpenFileName(this,"需要被打开的文件","这里填的是需要被打开的文件的路径","(*.txt);;(*.xmind)");
        //然后就是打开文件那一系列操作
    });



    //如何实现右键菜单？
    //首先要学会创建菜单,然后再实现you'jian右键打开菜单
    //右键菜单到底是什么操作方法？菜单还可以只有点击了才显示的方法吗？
    connect();





}

