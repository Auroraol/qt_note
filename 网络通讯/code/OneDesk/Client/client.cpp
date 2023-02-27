#include "client.h"

#include <QBuffer>
#include <QGuiApplication>
#include <QScreen>
#include <QSettings>

#define SERVER_PORT 44444  //服务器端口号
extern QMutex g_bufferLocker_;
extern QList<QByteArray> g_BufferList_;//图片数据

Client::Client(QWidget* parent)
    : QWidget(parent)
{
    clientSocket = new QTcpSocket;
    clientSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1); //尝试优化套接字以降低延迟
    loadSettings();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Client::sendData);
}

Client::~Client()
{
}

// 设置配置文件
void Client::loadSettings()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("REMOTEDESKTOPSERVER"); // 开始群组
    QString ServerHost = settings.value("ServerHost").toString();
    if(ServerHost.isEmpty())
    {
        ServerHost = "127.0.0.1";
        settings.setValue("ServerHost", ServerHost);
    }
    int ServerPort = settings.value("ServerPort", 0).toInt();
    if(0 == ServerPort)
    {
        ServerPort = SERVER_PORT;
        settings.setValue("ServerPort", ServerPort);
    }
    settings.endGroup();  // 结束群组
    settings.sync();
    //链接(建立链接）   参数: 服务器ip 服务器端口
    clientSocket->connectToHost(ServerHost, ServerPort);
    startPassiveConnect();
}

//被监控端启动
void Client::startPassiveConnect()
{
    // 通讯
    connect(clientSocket, &QTcpSocket::readyRead, this, [ = ]()
    {
        // 接收:  接收开始监控命令, 开始传输客户端桌面数据
        QString resStr;
        method.readMsg(clientSocket, &resStr);
        if (resStr.compare("CLIENT_START_MONITOR") == 0)
        {
            // 发送:  桌面数据, 每隔20ms
            timer->start(20);
        }
    });
}
QImage Client::CatchScreen()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    return screen->grabWindow(0).toImage();  // 返回QImag
}

// 发送:  桌面数据, 每隔20ms
void Client::sendData()
{
    QByteArray data;
    g_bufferLocker_.lock();
    if (g_BufferList_.size() > 0)
    {
        data = g_BufferList_.takeFirst();  // list[0], 发的是图片
    }
    g_bufferLocker_.unlock();
    if (data.length() > 0)
    {
        method.sendImg(clientSocket, data, Qimages_send);
    }
}


