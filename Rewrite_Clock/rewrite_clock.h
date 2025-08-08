#ifndef REWRITE_CLOCK_H
#define REWRITE_CLOCK_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Rewrite_Clock; }
QT_END_NAMESPACE

class Rewrite_Clock : public QWidget
{
    Q_OBJECT

public:
    Rewrite_Clock(QWidget *parent = nullptr);
    ~Rewrite_Clock();

private:
    Ui::Rewrite_Clock *ui;
};
#endif // REWRITE_CLOCK_H
