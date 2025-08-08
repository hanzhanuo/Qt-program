#ifndef INTEGRATE_VIDEO_H
#define INTEGRATE_VIDEO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Integrate_Video; }
QT_END_NAMESPACE

class Integrate_Video : public QWidget
{
    Q_OBJECT

public:
    Integrate_Video(QWidget *parent = nullptr);
    ~Integrate_Video();

private:
    Ui::Integrate_Video *ui;
};
#endif // INTEGRATE_VIDEO_H
