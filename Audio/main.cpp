#include "audio.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Audio w;
    w.Audio_Handle();
    w.show();
    return a.exec();
}
