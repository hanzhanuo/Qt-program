#include "widget.h"
#include "ui_widget.h"

#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.drawEllipse(300,300,200,200);   //画表盘，所以是画最大秒针还大的圆形，


    painter.drawLine();    //秒针
    painter.drawLine();
    painter.drawLine();

    //但是这些drawLine没有返回值该怎么办？怎么区分时分秒？

    //设置时间
    m_id=startTimer(1000);

    QTimer *tm = new QTimer(this);

    connect(tm,connect(tm,&time))

    connect()
}



