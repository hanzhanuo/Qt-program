#ifndef TCP_CILENT_H
#define TCP_CILENT_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class TCP_cilent; }
QT_END_NAMESPACE

class TCP_cilent : public QWidget
{
    Q_OBJECT

public:
    TCP_cilent(QWidget *parent = nullptr);
    ~TCP_cilent();

private:
    Ui::TCP_cilent *ui;

    //step1：socket操作
    QTcpSocket* m_socket=new QTcpSocket(this);
    //这种想要写为堆对象的，我都直接在头文件进行初始化，这个就是我的习惯

    //父对象无脑填this指针一定不会错，但是想要写的更好一点，就最好想一下再填
};
#endif // TCP_CILENT_H
