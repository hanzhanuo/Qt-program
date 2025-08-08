#include "EmployeeSystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EmployeeSystem system;
    system.show();

    return app.exec();
}
