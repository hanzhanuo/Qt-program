#ifndef HTTP_CILENT_H
#define HTTP_CILENT_H

#include <QWidget>
//因为http的重点就是三个类，所以首先无脑把这三个类包含进来
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class HTTP_cilent; }
QT_END_NAMESPACE

class HTTP_cilent : public QWidget
{
    Q_OBJECT

public:
    HTTP_cilent(QWidget *parent = nullptr);
    ~HTTP_cilent();
    
    void Audio_Create();

public slots:
    void network_connect();

private:
    Ui::HTTP_cilent *ui;


    //get函数必须传入一个右值引用的对象，所以这里传入栈对象到底行不行？试一试
};
#endif // HTTP_CILENT_H
