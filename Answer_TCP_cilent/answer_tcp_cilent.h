#ifndef ANSWER_TCP_CILENT_H
#define ANSWER_TCP_CILENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Answer_TCP_cilent; }
QT_END_NAMESPACE

class Answer_TCP_cilent : public QWidget
{
    Q_OBJECT

public:
    Answer_TCP_cilent(QWidget *parent = nullptr);
    ~Answer_TCP_cilent();

private:
    Ui::Answer_TCP_cilent *ui;
};
#endif // ANSWER_TCP_CILENT_H
