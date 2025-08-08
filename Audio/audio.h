#ifndef AUDIO_H
#define AUDIO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Audio; }
QT_END_NAMESPACE

class Audio : public QWidget
{
    Q_OBJECT

public:
    Audio(QWidget *parent = nullptr);
    ~Audio();

    void Audio_Handle();


private:
    Ui::Audio *ui;
};
#endif // AUDIO_H
