#ifndef INTEGRATE_AUDIO_H
#define INTEGRATE_AUDIO_H

#include <QWidget>
#include <QMediaPlayer>   //一定不要记错了类，我多少次了都是对于这个类的类名记错了
#include <QUrl>
#include <QFileDialog>   //即使是文本对话框调用本地的内容，也是必须要使用到url饿
#include <QPushButton>
#include <QSlider>
#include <QProgressBar>
#include <QLabel>
#include <QTime>    //这个是用来计算时间的。所以用来设置定时器的并不能用来设计时间
#include <QTimer>   //这个是用来设置定时器的
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {class Integrate_Audio;}
QT_END_NAMESPACE

class Integrate_Audio : public QWidget
{
    Q_OBJECT

public:
    Integrate_Audio(QWidget *parent = nullptr);
    ~Integrate_Audio();

    void musicopen();   //打开音乐
    void ButtonConnect();  //按键功能集成
    void volumeslider();  //音量调节
    void playprogress();  //播放进度调节
    void labelshow();   //显示播放时长

public slots:
    void update_position();
    void seek_position();

private:
    Ui::Integrate_Audio *ui;

    //对于暂时想不到设计什么数据成员的时候，就都一律写成局部变量，在有必要的时候再回来设计为数据成员
    //(不过上面说的写法仅限于对于Qt，对于cpp的设计思维仍然要是：先设计出行为和状态，再对他们进行实现)

    //尽可能养成写槽函数以及写数据成员的习惯。
    //如果单纯习惯了写lambda表达式，就会导致代码耦合程度非常高，不适合c++的设计模式了
    //所以这道综合题还是在锻炼我的设计模式



    QMediaPlayer* mp_player=new QMediaPlayer(this);
    QSlider* mp_pgsSlider=new QSlider(Qt::Horizontal,this);
};
#endif // INTEGRATE_AUDIO_H
