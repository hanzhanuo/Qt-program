#include "answer_tcp_cilent.h"
#include "ui_answer_tcp_cilent.h"

Answer_TCP_cilent::Answer_TCP_cilent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Answer_TCP_cilent)
{
    ui->setupUi(this);
}

Answer_TCP_cilent::~Answer_TCP_cilent()
{
    delete ui;
}

