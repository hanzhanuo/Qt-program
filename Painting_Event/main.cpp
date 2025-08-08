#include "paintevent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintEvent w;
    w.show();
    return a.exec();
}
