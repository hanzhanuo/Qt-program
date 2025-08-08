#include "answer_tcp_server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Answer_TCP_server w;
    w.show();
    return a.exec();
}
