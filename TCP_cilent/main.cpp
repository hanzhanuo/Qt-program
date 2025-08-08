#include "tcp_cilent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCP_cilent w;
    w.show();
    return a.exec();
}
