
#include <QtCore/QCoreApplication>
#include <QApplication>
#include "picthread.h"
#include "server.h"
#include "udpserver.h"
#include <QTextCodec>
#include <QTextStream>
#include <QFileInfo>
#include <QTextCodec>

int main(int argc, char* argv[])
{
    //解决中文乱码问题。
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //
    QApplication a(argc, argv);
    UdpServer* udp = new UdpServer();
    PicThread* picThread = new PicThread();
    picThread->start(); // 开启线程
    Server* server = new Server();
    QObject::connect(udp, SIGNAL(lockMouseSignal(bool)), server, SLOT(lockerMouseSlot(bool)));
    return a.exec();
}
