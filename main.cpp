#include "gamecore.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameCore w;
    w.show();

    return a.exec();
}
