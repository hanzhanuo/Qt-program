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

    void HLayout();    //水平布局
    void VLayout();    //垂直布局
    void GridLayout(); //网状布局
    void FormLayout(); //表格式布局

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
