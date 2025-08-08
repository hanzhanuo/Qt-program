#include "fileexplorer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FileExplorer explorer;

    explorer.show();

    return app.exec();
}
