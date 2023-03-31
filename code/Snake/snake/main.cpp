#include "snakegame.h"
#include <QTime>
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qsrand((unsigned int)time(NULL));
    SnakeGame w;
    w.show();
    return a.exec();
}
