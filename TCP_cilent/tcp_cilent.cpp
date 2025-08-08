#include "tcp_cilent.h"
#include "ui_tcp_cilent.h"

#include <QByteArray>
#include <QString>
#include <QListView>

TCP_cilent::TCP_cilent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCP_cilent)
{
    ui->setupUi(this);

    //step2：connect操作
    m_socket->connectToHost("127.0.0.1",8080);
    //这里的ip地址填的是网络环回地址

    //step3：readyRead信号函数操作
    //——————好像是只要connect完了，就只需要安静等待这个标志位即可

    connect(m_socket,&QTcpSocket::readyRead,[=](){   //因为是read准备好了，所以对应的槽函数一定是读操作，而不是写操作
        //读数据操作总共就三种：read，readall，readline。
        //然后基本上都只会选readall，这是最优读取方法

        QByteArray info=m_socket->readAll();
        //这里的返回值获取思路以及所有代码的返回值获取思路:
        //全都是先写等号右边的函数调用，
        //然后光标放到调用的函数上，就能知道进一步该传入什么参数，并且使用什么样的返回值进行承接了
        //所以这个先把函数调用出来，然后再放上光标或者通过助手进行查找，就能知道该怎么传参和承接返回值了


        ui->cilent_list_view->addItem(QString("客户端接收的服务器数据为")+QString::fromUtf8(info));
        //这种写法非常非常经典，基本上在所有的综合性作业中都出现了。可以说是以后项目的必用写法格式
        //这个格式的特点：一个是bytearray的转化，一个是字符串的拼接操作
        //并且这里第一个QString中原本是C风格字符串，然后通过QString包裹从而实现了强转操作

    });


}

TCP_cilent::~TCP_cilent()
{
    delete ui;
}


void TCP_cilent::on_cilent_Button_clicked()
//这个等价于connect函数一步到位了。
//所以原本这个函数原本是可以化为connect函数，写在上面读操作的connect函数的紧邻着位置的
{
    //并且这里要注意：只有读操作受readyRead限制，写操作只取决于自己想什么时候发。
    //所以一定是读操作使用readyRead信号槽，写操作使用clicked信号槽，两者等待的信号一定是不同的

    //思路：先从lineedit中获取内容，然后当按下发送按钮的时候write出去，然后再清空lineedit的内容
    //获取内容：
    QString info=ui->cilent_Edit->text();
    //发送数据
    m_socket->write(info.toUtf8());


    //展示数据：(展示到聊天框的listwidget屏幕上)
    ui->cilent_list_view->addItem(QString("客户端向服务端发送的数据为:")+info);

    //清空发送框
    ui->cilent_Edit->clear();
}
