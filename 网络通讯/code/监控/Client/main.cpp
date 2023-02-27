#include "client.h"

#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QFileInfo>

int main(int argc, char* argv[])
{
    //解决中文乱码问题。
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //
    QApplication a(argc, argv);
    Client w;
    w.show();
    return a.exec();
}
