#include "answer_tcp_server.h"
#include "ui_answer_tcp_server.h"


#include <QMessageBox>
#include <QTcpSocket>

Answer_TCP_server::Answer_TCP_server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Answer_TCP_server)
{
    ui->setupUi(this);

    setWindowTitle("Tcp Server");
        resize(600, 480);

        //1、创建QTcpServer的对象，目的就是为了监听
        m_tcpServer = new QTcpServer(this);

        //3、连接信号与槽，有新的连接就执行槽函数
        connect(m_tcpServer, &QTcpServer::newConnection, this, &Widget::handle);

        //2、监听客户端的连接
        bool ret = m_tcpServer->listen(QHostAddress::Any, 8888);
        if(!ret)
        {
            QMessageBox::critical(this, "严重错误", "监听失败");
            return;
        }
}

Answer_TCP_server::~Answer_TCP_server()
{
    delete ui;
}

void Answer_TCP_server::handle()
{
    //4、得到通信的对象QTcpSocket
        QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();

        //5、连接信号与槽，只要该信号被发出，就说明客户端有数据发过来了
        connect(clientSocket, &QTcpSocket::readyRead, [=]{
            ui->listWidget->addItem(">>>客户端连接上来了...");

            //接收的客户端的数据
            QByteArray ba = clientSocket->readAll();

            ui->listWidget->addItem(QString(">>>服务器--接收--了客户端的数据:")
                                     + QString::fromUtf8(ba));
            //接下来可以对数据进行处理

            //将处理好之后的数据发送给客户端
            clientSocket->write(ba);
            ui->listWidget->addItem(QString("<<<服务器==发送==数据给客户端:") +
                                    QString::fromUtf8(ba));
        });

        //6、连接信号与槽，连接断开的时候，需要做哪些后续的处理
        connect(clientSocket, &QTcpSocket::disconnected, [=]{
            //关闭监听的对象
            m_tcpServer->close();
            //清理QTcpSocket的资源
            clientSocket->deleteLater();
            //将窗口关闭
            close();
        });
}

