#include "my_label.h"
#include <QDebug>
#include <QMouseEvent>



My_label::My_label(QLabel *parent)
    :QLabel(parent)

{
    //无论什么的事件过滤器都是装在构造函数中的，所以只要需要使用事件过滤器的方法进行筛选重写

    installEventFilter(this);   //进行过滤器的注册
}

void My_label::enterEvent(QEvent *event)
{
    Q_UNUSED(event);    //当使用这个宏函数的时候，就会保证不会报未使用的警告
    //所以这个宏是专门用来处理不得不传指针，但是这个指针还用不到的情况

    qDebug()<<"鼠标已进入";
    //其实这个作为进入操作，应该是任何内容的进入都会触发这个事件，所以这里写有东西进入都是可以的
}

void My_label::leaveEvent(QEvent *event)
{
    qDebug()<<"有东西出去了";
}



void My_label::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        //之前一直有问题是因为一直没有包含QMouseEvent头文件。
        //所以以后在写任何内容的时候，只要报错首先查这个函数的头文件有没有包含。
        //Qt因为是个集成软件，所以没包含问题属于极其常见的问题

        qDebug()<<"鼠标左键按压了";
        qDebug()<<"横坐标："<<ev->x();
        qDebug()<<"纵坐标："<<ev->y();

    }
}


void My_label::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons()&Qt::LeftButton){
        //注意这里的按位与和上面的双等号之间的区别
        //基本可以归纳为：
        //当使用的成员函数是复数形式的时候，就需要通过按位与来确定具体是哪个枚举值
        //当使用的成员函数是单数形式的时候，就通过双等号确定是哪个枚举值


        qDebug()<<"鼠标左键拖动了";
        qDebug()<<"横坐标："<<ev->x();
        qDebug()<<"纵坐标："<<ev->y();

    }
}

void My_label::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::RightButton){   //这个好像也是只能通过积累其合理性，没别的办法了吗？

        qDebug()<<"按键被释放了";
    }
}

bool My_label::event(QEvent *ev)
{
    if(ev->type()==QEvent::MouseMove){
        qDebug()<<"event对鼠标移动事件拦截了";

        //所以我是不是可以理解为：
        //因为event是比具体的事件更低级的内容，所以event基本都是对应着整个QEvent的枚举值
        //因为每个具体的事件是比event更高级的父类，所以使用的就是整个Qt的枚举值


        return true;
        //必须必须要return true，否则就会导致接着往下走，交付基类。
        //此时就起不到对事件拦截的效果了，会导致接着执行其他事件的结果

        //然后另一个问题就是：这个event函数就像线程一样，是会借助exec函数实现无限执行的。
        //这就是为什么对于事件函数不需要进行调用，只需要定义。
        //不需要调用的原因就是它会像线程函数一样，不断的进行调用。所以自然不需要人手动调用了

    }else if(ev->type()==QEvent::MouseButtonDblClick){
        //我感觉现在能明白了：这里的使用什么函数和使用哪个位置的枚举值是完全对应的。
        //所以只要找到了函数，往上下稍微翻一翻，一定能找到对应需要使用的枚举值
        //所以现在就转换为了找函数的问题：查找方法就是先找到整个大类QMouseEvent，然后再对于这个大类进行助手查找
        //然后重头戏来了：对于返回值，参数列表，函数名三个内容，只要是点开的，都点进去看看。
        //就比如这里的button，就一定是到大类QMouseEvent中去找，然后因为是和按钮有关的，所以就一定是button
        //然后再从button的参数列表和返回值中找线索
        //所以找可以写什么(最典型的就是找枚举值可以写什么)，就像是在破案，只要是能点开的都点进去看看



        qDebug()<<"event对鼠标点击事件拦截了";

        return true;
    }

    return QLabel::event(ev);
}

bool My_label::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj==this){
        if(ev->type() == QEvent::MouseButtonPress)

               {
                   QMouseEvent *event = static_cast<QMouseEvent *>(ev);

                   //如果是鼠标左键按压
                   //这里一定是先确定是鼠标按压，然后再确定是左键按压的。
                   //因为两者的主语不是在一个层面上的，所以必须要对主语进行进一步的细化，所以才需要写两个if的
                   if(event->button() == Qt::LeftButton)
                   {
                       qDebug() << "eventFilter 鼠标左键被按压了,横坐标x = "
                                << event->x() << ", 纵坐标y = " << event->y();
                        return true;
                   }
               }
           }

           return QLabel::eventFilter(obj, ev);
}

