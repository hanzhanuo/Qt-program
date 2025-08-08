#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;


    w.Dialog_create();
    w.show();
    return a.exec();
}
