#include "integrate_video.h"

#include <QApplication>

//对于视频部件，除了布局不一样，其他的都是完全相同。所以对于网格布局的起点和长度的写法要熟练，对于那个splitter的项目也要完全做出来
//对于音乐播放器的声音还没做出来，我认为和手动设置进度条应该是一模一样的
//所以真正的工作重心应该是先把splitter和前面三个项目都给解决掉(即包括计算器项目)，然后再把这个音乐播放器重新解决一遍
//然后对于这个视频播放器不应该着急进行处理

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Integrate_Video w;
    w.show();
    return a.exec();
}
