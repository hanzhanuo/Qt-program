#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <QListView>
#include <QStringListModel>    //用来存储数据的string list容器

#include <QTreeView>
#include <QStandardItemModel>
//除了list视图使用stringlist，其余的视图都是使用这种标准模型作为存储模型的

#include <QTableView>


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

void Widget::List_view()
{
    /*
    四步走：
    1.先添加数据到容器(此时就要使用到容器)
    2.创建模型并和容器关联
    3.创建视图
    4.模型和视图关联
    */

    //step1：添加数据
    QStringList str_lst;
    str_lst<<"nihao"<<"nihaoma";    //切记是输出流运算符，我就总是写成输入流运算符
    //并且此时这个内容在显示结果里也是可以使用的，所以所有的视图模型有可能都可以设置属性，从而使得表格不可修改
    //关联到现实中的不可修改的表格，是不是可以设置一个按钮，然后按钮触发connect，从而使得整个表格的属性为不可修改


    qDebug()<<"sizeof(str_lst)"<<sizeof(str_lst);
    //step2：创建模型并关联容器
    QStringListModel* p_slm=new QStringListModel(str_lst,this);
    //模型-视图架构中的模型类就是这么写的，所以是先有了QStringListModel，然后才引出的QStringList
    //所以一定不要对模型-视图架构中最重要的来那个环节之一这么不熟练

    //step3：创建视图
    QListView* p_lv=new QListView(this);
    p_lv->resize(300,300);
    p_lv->move(200,100);

    //step4:模型视图关联
    p_lv->setModel(p_slm);
    //所以以后要记住，对于毫无意义的指针可以使用缩写，对于但凡有点意义的，一定要用有意义的名称明名
    //用有意义的命名是为了在全局再次进行调用的时候，能增加代码可读性，更好理解，不用更多的浪费自己的脑子了

    //所以这里更好的写法是这样：view->setmodel(view);


}

void Widget::Tree_view()
{

    //对整个模型添加数据，就是树形结构的父节点

    //对每一层添加row，就是下面的依次添加

    //qstringlist的传左值右值应该都是没区别的




    //和list一模一样的步骤：先进行数据存储
    QList<QStandardItem*> rootItem;
    //这就是非QStringList的处理形式————即QStringList其实就是QList<String>

    QStandardItem* p_qsi1=new QStandardItem("1");
    QStandardItem* p_qsi2=new QStandardItem("初中部");

    rootItem.push_back(p_qsi1);
    rootItem.push_back(p_qsi2);

    //创建模型————所以除了list形式以外，其他两种形式都是使用standarditem的
    QStandardItemModel* p_model=new QStandardItemModel(this);   //因为其他几个参数不认识，所以就直接用第一个参数的形式了



    //进行模型和视图的关联：
    p_model->appendRow(rootItem);
/*
    这一步就相当于列表视图中的：创建模型并关联容器了。所以此时并没有完成模型和视图之间的关联
    所以所有的这几种视图步骤上基本都是一样的，
    树型视图看似折腾的更多，其实就是在折腾模型，而不是折腾视图
    三大中视图类型的写法都是一样的———————全部都是一行结束
*/


    //进行树形模型的进一步添加子节点的操作(这个就是树形模型比其他模型更多的地方)
    QList<QStandardItem*> secondfloor;
    //切记，这里的尖括号内填的是元素的单位，所以一定是以item结尾的,所以不可能是model结尾的
    //这个以谁结尾非常非常容易混

    //这种向容器中添加内容的操作，和向布局中添加内容是一模一样的：都是创建内容，然后一个个添加进去
    //所以按照对布局的操作走的思路来写就思路清晰了
    QStandardItem* p_qsi11=new QStandardItem("11");
    QStandardItem* p_qsi12=new QStandardItem("初一");
    secondfloor.push_back(p_qsi11);
    secondfloor.push_back(p_qsi12);

    p_qsi1->appendRow(secondfloor);
    //一定要切记容器和指针之间的关系：即创建父子关系一定是树形结构中的指针关联容器，
    //主语和宾语的性质首先就一定一定不能错


    QList<QStandardItem*> thirdfloor;
    QStandardItem* p_qsi111=new QStandardItem("111");
    QStandardItem* p_qsi112=new QStandardItem("一班");

    thirdfloor.push_back(p_qsi111);
    thirdfloor.push_back(p_qsi112);

    p_qsi11->appendRow(thirdfloor);
    //所以仍然是和设置布局非常非常像的三步走操作，这里只需要消息最后一步的指针和容器即可
    //并且一定是每创建一个节点，都要进行一次list容器的创建。即这些步骤都需要重新进行一次
    //这里的指针的含义是挂载到哪个父节点上面，这个非常非常容易错，一不小心就容易挂错了父节点

    //至此构建树的模型结构完毕


    //此时才开始进行模型创建和模型视图关联的操作
    QTreeView* p_treeview=new QTreeView(this);
    p_treeview->resize(400, 300);
    p_treeview->move(100, 100);

    //进行模型和视图的转换
    p_treeview->setModel(p_model);


    //添加属性的操作：从结果上看，添加属性的操作写在任何位置都可以，所以最好写在所有都关联好了的最后面。
    //即把整个四步的关联步骤给视作一个整体先处理出来

    //添加水平表头(添加属性操作)
    p_model->setHorizontalHeaderLabels(QStringList()<<"编号"<<"部门");
    //这里使用QStringList意味着，不管是什么结构，在设置表头的时候，都应该优先倾向于使用QStringList来处理
    //并且由于好像每个模型都能设置表头，所以这里的QStringList是每个模型都这样使用

    //还可以添加树的不可改变属性，等待会有时间再添加




}    //end of functiong tree_view


void Widget::Table_view()
{


//    项目视图和项目部件都是使用setitem函数进行设置的，并且用法是完全一模一样的

    QStandardItemModel* p_model=new QStandardItemModel(this);
    //所以属性属于是模型的属性，而不是视图的属性，所以最好还是直接贴着模型写吧

    //设置属性：表头设置
    //p_model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    //p_model->setVerticalHeaderItem(0,new QStandardItem("姓名"));
    //能设置水平表头，能不能设置垂直表头？
    //所以上面这种写法印证了对于表格视图，是一定可以横纵表头都进行设置的

    QStringList H_headerlist;
    H_headerlist<<"学号"<<"姓名"<<"性别"<<"成绩";
    for(size_t idx=0;idx<4;idx++){
        p_model->setHorizontalHeaderItem(idx,new QStandardItem(H_headerlist.at(idx)));
    }

    QStringList V_headerlist;
    V_headerlist<<"1"<<"2"<<"3";
    for(size_t idx=0;idx<3;idx++){
        p_model->setVerticalHeaderItem(idx,new QStandardItem(V_headerlist.at(idx)));
    }
    //由于横纵坐标个数不相等，所以这里设置两个不同的for循环来处理


    //进行类似容器的对于表格模型进行内容添加

    QList<QStandardItem*> numlist;
    numlist<<new QStandardItem("191102")<<new QStandardItem("191102")<<new QStandardItem("191102");

    QList<QStandardItem*> namelist;
    namelist<<new QStandardItem("杨逍")<<new QStandardItem("张三丰")<<new QStandardItem("赵敏");

    QList<QStandardItem*> sexlist;
    sexlist<<new QStandardItem("男")<<new QStandardItem("男")<<new QStandardItem("女");

    QList<QStandardItem*> gradelist;
    gradelist<<new QStandardItem("680")<<new QStandardItem("700")<<new QStandardItem("748");

    for(size_t idx=0;idx<4;idx++){
        size_t col=0;
        p_model->setItem(idx,col++,numlist.at(idx));
        //以后都用这种at写法代替直接中括号，效果是能进行越界检查，能避免悄无声息的报错
        p_model->setItem(idx,col++,namelist.at(idx));
        p_model->setItem(idx,col++,sexlist.at(idx));
        p_model->setItem(idx,col++,gradelist.at(idx));
}
        /*
    这里不能用for循环的写法来写—————原因分析
    setItem的第三个参数必须是QStandardItem的对象，而QSTlist数组又只能存字符串，不能存其他任何东西
    所以如果还想要写，就不能使用QStringList数组存储，只能使用QList<QStandardItem>写
    ——————好像这样使用运算符重载也是被允许的！所以并不是被禁止了，仍然有效
*/

    //至此才是所有数据添加到模型中添加成功，后面还需要和视图进行关联
    QTableView *tableView = new QTableView(this);
    tableView->resize(800, 600);

    //2、调用setModel
    tableView->setModel(p_model);

    //6、其他操作
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    p_model->sort(0, Qt::DescendingOrder);


}  //end of func Table_view;

void Widget::List_widget()
{
    //这个写法我也想尝试使用for循环写，待会用qstring写了看看

}



