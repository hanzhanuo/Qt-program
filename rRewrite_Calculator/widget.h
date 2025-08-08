#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }   //有ui界面就会自动添加这个ui的界面
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



signals:   //放置信号函数
private slots:   //放置槽函数
    //自定义槽函数必须在信号关键字 后面进行定义，并且slots的private并不属于private，privvate要另外写

    void When_Digit_Clicked();
    void When_Operator_Clicked();
    void When_Equal_Clicked();
    void When_Clear_Clicked();
    //至于槽函数是怎么分的，这就需要对于代码逻辑进一步抽象了
    //——————即当能抽象出某些代码逻辑是完全相同的的话，其实就可以写在同一个槽函数中
    //就比如这里的所有数字，一定是使用同一种处理逻辑的。总的来说这就是槽函数的设计逻辑


private:   //基本上用来放置数据成员还有私有的一些成员函数

    //从数据成员的选项可以看出，每个数据成员都可以自动设置getter和setter函数，所以这两种函数已经是数据成员的标配操作行为了
    Ui::Widget *ui;
    QString m_current_Input;
    QString m_pending_Operator;
    double m_result;
    bool m_Waiting_Operator_Flag;


    void ConnectFunc();
};


//不能轻易自己写类，还是尽可能使用Qt提供的类，或者必须把所有需要适配的内容都写进来，才能放心使用


//class Calculator: public QWidget{    //所以在Qt中，有必要的时候必须要创建类。所以不要忘了c++11中的任何知识点，在Qt中都是可以使用的
//    Q_OBJECT

//public:    //放置成员函数
//    explicit Calculator(QWidget *parent = nullptr);
//    ~Calculator();

//signals:   //放置信号函数
//private slots:   //放置槽函数
//    //自定义槽函数必须在信号关键字 后面进行定义，并且slots的private并不属于private，privvate要另外写

//    void When_Digit_Clicked();
//    void When_Operator_Clicked();
//    void When_Equal_Clicked();
//    void When_Clear_Clicked();
//    //至于槽函数是怎么分的，这就需要对于代码逻辑进一步抽象了
//    //——————即当能抽象出某些代码逻辑是完全相同的的话，其实就可以写在同一个槽函数中
//    //就比如这里的所有数字，一定是使用同一种处理逻辑的。总的来说这就是槽函数的设计逻辑


//private:   //基本上用来放置数据成员还有私有的一些成员函数
//    Ui::Widget *ui;
//    QString m_current_Input;
//    QString m_pending_Operator;
//    double m_result;
//    bool m_Waiting_Operator_Flag;


//};
#endif // WIDGET_H
