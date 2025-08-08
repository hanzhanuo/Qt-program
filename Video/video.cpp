#include "video.h"
#include "ui_video.h"


#include <QMediaPlayer>
#include <QVideoWidget>   //这个就是所谓的分层设计的部件，所以是相比于音频，新增了这个类

#include <QPushButton>
#include <QFileDialog>   //这个是在音视频的打开文件中必须要使用的库

#include <QVBoxLayout>   //由于视频的功能按键更多了，所以就必须要使用layout部件
//当想要使用一些更复杂的布局的时候，就可以使用gridlayout来实现


Video::Video(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Video)
{
    ui->setupUi(this);
}

Video::~Video()
{
    delete ui;
}

void Video::Vedio_Handle()
{
    //因为是两个类，所以就要两个类分别创建对象：所以就是相比于音频，单纯是多了一个需要创建的对象而已

    QMediaPlayer* media=new QMediaPlayer(this);
    //这个的参数列表中看似是两个参数，但是其中一个参数中有默认参数，所以只写一个参数就够了

    QVideoWidget* veido=new QVideoWidget(this);

    media->setVideoOutput(veido);
    //这步没办法，记住就好了，可以理解为是两个类之间必须要创建的关联就好了


    QPushButton *select_btn = new QPushButton("点击选择视频", this);

        connect(select_btn, &QPushButton::clicked, [=]{
            QString path = QFileDialog::getOpenFileName(this, "xxx","文件路径","文件过滤项");
            //如果后两个参数不写的话，就是默认从这个项目的本地路径打开。所以最好还是无脑写上

            media->setMedia(QMediaContent(path));
            media->play();
    });
    //这整个connect函数都和音频的connect函数一模一样，没有任何区别


        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(vedio);
        layout->addWidget(select_btn);
        setLayout(layout);

        //总结：除了多了一步setVideoOutput()函数来实现的关联操作以外，其他的操作都是一模一样的
        //所以音视频无非是多了个对象并且多了个对于对象的关联操作罢了
}

