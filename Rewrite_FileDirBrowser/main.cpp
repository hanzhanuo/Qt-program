#include "filebroswer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileBroswer w;
    w.show();
    return a.exec();
}
