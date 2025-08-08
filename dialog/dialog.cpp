#include "dialog.h"

#include <QPushButton>
#include <QDialog>
#include <QDebug>

#include <QMessageBox>

#include <QFileDialog>
//想要文字被表现出来，就一定要使用文本编辑部件。
//尤其是对于这种大型文本，就更需要使用多行文本编辑器这种无限制的文本编辑部件了
#include <QPlainTextEdit>
#include <QFile>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    resize(600,480);
}

Dialog::~Dialog()
{
}

void Dialog::Dialog_create()
{
    //模态对话框从而创建栈对象
    QPushButton *btn1 = new QPushButton("模态对话框按钮，栈对象", this);
    btn1->move(100, 100);
    btn1->resize(300, 50);

    connect(btn1,&QPushButton::clicked,[=](){
        QDialog dlg;
        dlg.exec();   //模态对话框的实现效果就是使用这个函数直接进行阻塞
    });



    //非模态对话框从而创建堆对象
    QPushButton *btn2 = new QPushButton("非模态对话框按钮,堆对象", this);
    btn2->move(100, 200);
    btn2->resize(300, 50);


    connect(btn2,&QPushButton::clicked,[=](){
        QDialog* p_dlg=new QDialog(this);

        p_dlg->show();
        //注意这里是对于对话框的展示，而不是对于整个widget的展示
        //所以是一定不要畏惧在对话框里写show函数，这是非模态对话框的最最必要函数
    });

}    //end of Dialog_create;

void Dialog::Message_dialog()
{
    //消息对话框完全和log4cpp一模一样

    QPushButton *messBtn = new QPushButton("消息对话框按钮", this);
    messBtn->resize(300, 50);
    messBtn->move(100, 100);

    //对话框基本上都是靠connect来实现的，
    //所以对话框在外部基本上使用不到什么set函数，基本上都是直接进入connect写核心内容

    connect(messBtn,&QPushButton::clicked, [=](){

        //这些因为有小括号，所以是静态成员函数，而不是枚举值。所以不要类型判断错误了
        QMessageBox::critical(this,"严重错误","这是严重类型的错误");
        QMessageBox::information(this,"信息提示","这是一条信息提示");
        QMessageBox::question(this,"问题提示","此时出现问题了");
        QMessageBox::warning(this,"警告信息","严重警告");

        //注意：这里的每个标准对话框不是一个个的对象，所以没法进行move操作和layout操作。所以他们的位置一定是不变的
        //第一个字符串参数是小标题，第二个字符串参数是居中的主要提示文字
        //这两个一定要能区分的清楚


    });   //end of connect func

}    //end of func Message_dialog;

void Dialog::File_dialog()
{

    QPushButton *fileBtn = new QPushButton("测试文件对话框", this);
    fileBtn->resize(300, 50);
    fileBtn->move(100, 400);


    QPlainTextEdit *pte = new QPlainTextEdit(this);
    pte->move(450, 50);
    pte->resize(500, 700);

    //由于需要使用大型文本编辑部件了，所以相比于其他对话框，就需要多创建一个文本编辑部件对象
    connect(fileBtn,&QPushButton::clicked,[=](){
    QString path=QFileDialog::getOpenFileName(this,"需要被打开的文件","这里填的是需要被打开的文件的路径","(*.txt);;(*.xmind)");
    /*
    对于这个函数的参数的解读：
    第二个参数就像消息对话框一样，都是在左上角的语句
    第三个参数是文件资源的路径(这里只是巧了要打开文本文件，但其实这种对话框打开哪种文件都市可以的)
    第四个参数是当前路径下具体查找哪类资源的过滤器，即比如可以专门找jpg文件之类的
    */

    //QFileDialog::getOpenFileUrl()
    //从参数列表和返回值分析这个函数：这个函数返回值是Qurl，上面函数的返回值是QString
    //这个函数和上面函数唯一的不同就是这里的资源路径参数是URL路径，上面是本地文件路径
    //所以以后如果想使用网上资源文件就可以使用这个函数来设计对话框


    QFile file(path);   //由于path数据类型确实是QString，所以这样进行传入处理没毛病
    //这里就是创建一个栈对象，之所以创建栈对象，是因为这是一个模态对话框，
    //所以为了避免永远销毁不了，对于不管是什么内容的创建，就都使用栈对象了

    QFile* p_file=new QFile(path,this);
    //file.
    //p_file->
    //果然上面两个对象的可调用函数是一模一样的，但是为了非模态对话框，这里都果断创建栈对象即可

    file.open(QIODevice::ReadOnly);   //这里指的是打开方式参数，使用的是枚举值



    QByteArray ba=file.readAll();
    //这显然又是创建一个栈对象进行接收的案例，所以在非模态，尤其是在文件对话框中，全都无脑使用栈对象即可

    QString msg(ba);    //这里传入的是一个unicode数据类型，所以就是传入ba
    pte->setPlainText(msg);

    file.close();


    });
}  //end of func File_dialog;

