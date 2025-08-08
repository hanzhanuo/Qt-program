#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
//对于服务器端，一定是多一个类，然后写内容的时候也是多写一部分这个类的流程
//所以剩余流程相同，相比之下只是服务器端多了一部分流程
//所以每次先写的时候都先写客户端，客户端的内容会更好写一些，并且还具有复用性

QT_BEGIN_NAMESPACE
namespace Ui { class TCP_server; }
QT_END_NAMESPACE

class TCP_server : public QWidget
{
    Q_OBJECT

public:
    TCP_server(QWidget *parent = nullptr);
    ~TCP_server();

public slots:
    void handel_func;

private:
    Ui::TCP_server *ui;
    QTcpServer* m_tcpServer=new QTcpServer(this);
    //相比于客户端，多了服务器类。
    //所以从cpp的设计思想上来说，我认为就是因为客户端和服务器端都有socket类的代码逻辑，
    //所以使用的是进行代码复用的思想，
    //所以才会看似多出来这个server类，但其实根本上是因为把socket类给单独抽出来了而已

    QTcpSocket* m_socket=new QTcpSocket(this);

};
#endif // TCP_SERVER_H
