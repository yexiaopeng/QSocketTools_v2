#include "qsockettools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSocketTools w;
    w.show();

    return a.exec();
}
