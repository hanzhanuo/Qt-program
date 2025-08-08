#include "integrate_video.h"
#include "ui_integrate_video.h"

Integrate_Video::Integrate_Video(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Integrate_Video)
{
    ui->setupUi(this);
}

Integrate_Video::~Integrate_Video()
{
    delete ui;
}

