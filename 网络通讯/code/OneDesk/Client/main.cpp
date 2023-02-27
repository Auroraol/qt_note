#include "client.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    PicThread*  picThread  = new PicThread();
    picThread->start(); // 开启线程
    Client w;
    w.show();
    return a.exec();
}
