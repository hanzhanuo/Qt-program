#include "rewrite_clock.h"
#include "ui_rewrite_clock.h"

Rewrite_Clock::Rewrite_Clock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Rewrite_Clock)
{
    ui->setupUi(this);
}

Rewrite_Clock::~Rewrite_Clock()
{
    delete ui;
}

