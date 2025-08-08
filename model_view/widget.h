#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void List_view();
    void Tree_view();
    void Table_view();

    void test();

    void List_widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
