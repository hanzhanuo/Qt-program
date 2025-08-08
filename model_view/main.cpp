#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.List_view();
    w.Tree_view();
    w.Table_view();
    w.show();
    return a.exec();
}
