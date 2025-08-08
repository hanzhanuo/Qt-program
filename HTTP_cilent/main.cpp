#include "http_cilent.h"

#include <QApplication>

//http是有写法范式的，所以重点在于把所有步骤有线索的记下来，而不是写一通就算完事了

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HTTP_cilent w;
    w.show();
    return a.exec();
}
