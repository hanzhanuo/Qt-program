#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.Combo_box();
    w.Spin_box();
    w.Time_Calender();
    w.Slider();
    w.Sequence_Edit();
    w.show();
    return a.exec();
}
