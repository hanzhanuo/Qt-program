#include "tcp_server.h"
#include "ui_tcp_server.h"

#include <QMessageBox> //文件对话框和这种日志消息对话框的最后后缀名是不一样的

TCP_server::TCP_server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCP_server)
{
    ui->setupUi(this);

    bool ret=m_tcpServer->listen(QHostAddress::Any,8080);
    //在监听的时候，一定是默认监听所有ip地址的，所以设置的主机地址才为any
    //然后养成习惯：对于每个函数，在写出来之后都首先看返回值和参数列表，这样才能知道该如何进行承接

    //if(ret==false){
    //这样写不够优雅，在单位一定会被人骂的。所以要写为！取反的操作来实现false的表达
    //一定一定要熟练这种bool的写法，以后都这样写false的表达
    if(!ret){
        QMessageBox::critical(this,"严重错误","监听失败");
        //这种日志消息对话框一定一定要熟练，就是无脑两个字符串，一个是日志名一个是日志内容
    }


    connect(m_tcpServer,&QTcpServer::newConnection,this,&TCP_server::handel_func);
    //注意这个connect函数的两个类之间的区别：只要是涉及到了this指针，就一定是找到当前的类是什么类，这个不用犹豫
    //我对这里的掌握就是太不熟练了，所以就比较犹豫。但这里明知道使用的是this，就不应该犹豫了
    //并且在发现没雨槽函数的时候，就现在这里命名上，然后再在头文件中实现定义操作

}

TCP_server::~TCP_server()
{
    delete ui;
}

void TCP_server::handel_func()
{
    m_socket=m_tcpServer->nextPendingConnection();
    //这个就是accept函数，对标的是客户端的connectToHost()函数，
    //意味着从这里开始，后面的内容两者基本上都是一模一样的了

    connect(m_socket,&QTcpSocket::readyRead,[](){

    });


    //虽然上面说操作基本都是一模一样的了，但是这里还有个区别就是：
    //对于服务器端要通过编写代码实现资源回收，客户端通过手动close实现资源回收。这就是两者后面最大的不同
}

