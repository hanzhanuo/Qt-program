#include "audio.h"
#include "ui_audio.h"

//一定一定不要忘了在配置文件中加内容我这次又是一次忘记在配置文件中加内容了
#include <QMediaPlayer>
//这个就像tcpsocket和tcpserver之间的关系一样，是一种平行剥离出来的音视频共同需要的类

#include <QFileDialog>    //只要是音视频，基本上都是必须使用文本对话框的
#include <QPushButton>
#include <QString>

Audio::Audio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Audio)
{
    ui->setupUi(this);
}

Audio::~Audio()
{
    delete ui;
}

void Audio::Audio_Handle()
{
    QPushButton* select_btn=new QPushButton("点击选择音频文件",this);
    //这个重新写成员函数的做法打消了我的一个顾虑：
    //只要是成员函数，那么使用this指针就都是可行的，所以根本不用担心在任何位置想使用this指针会不会受影响

    QMediaPlayer *audio_palyer=new QMediaPlayer(this);


    //每次写connect函数的时候，都要先分析思路(即必须要分析出是谁在干什么，从而导致谁干什么)
    //比如这里就是按下按键，然后打开某个路径下的音频
    connect(select_btn,&QPushButton::clicked,[=](){
        QString path=QFileDialog::getOpenFileName(this,"不知道用来干什么的","音频文件的路径名","对于文件类型的过滤器");
        //这里其实也可以写传入URL的操作


        audio_palyer->setMedia(QMediaContent(path));
        //这个QMediaContent表示的是使用url作为参数，实现对于文件的打开操作的函数
        //并且这个函数在无论音频打开还是视频打开中，都是必须用的函数，所以要记熟

        //audio_palyer->setVolume(80);
        //这类connect函数写在任何位置都可以，所以setter函数理论上来说，写在connect函数的外面来实现配置即可

        audio_palyer->play();   //进行播放操作的函数
        //所以前面的所有都是在进行setter函数配置，只有这里是在最终实现play的操作

    });   //end of connect func


    audio_palyer->setVolume(80);   //所以这里就是把上面的在connect函数中进行配置的setter函数放在connect外面来实现了


}    //end of func Audio_Handle



