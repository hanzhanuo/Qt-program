#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Video; }
QT_END_NAMESPACE

class Video : public QWidget
{
    Q_OBJECT

public:
    Video(QWidget *parent = nullptr);
    ~Video();

    void Vedio_Handle();

private:
    Ui::Video *ui;
};
#endif // VIDEO_H
