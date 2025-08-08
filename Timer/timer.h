#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Timer; }
QT_END_NAMESPACE

class Timer : public QWidget
{
    Q_OBJECT

public:
    Timer(QWidget *parent = nullptr);
    ~Timer();

    void timerEvent(QTimerEvent* event) override;
    //这里明显也是一个设置Qxx* 的参数列表。这个参数列表具体是靠从助手那搜索才能知道的，所以不要懵

private:
    Ui::Timer *ui;
    int m_id1;
    int m_id2;
    int m_id3;
};
#endif // TIMER_H
