#include "udpserver.h"
#define UDP_SERVER_PORT 44446
#define UDP_CLIENT_PORT 44448

UdpServer::UdpServer(QObject* parent)
    : QObject(parent)
    , timer_(new QTimer(this))
{
    socket_ = new QUdpSocket(this);
    socket_->bind(UDP_SERVER_PORT, QUdpSocket::ShareAddress);  // 绑定自己端口号 参数:[服务器端口 ip]
    connect(socket_, &QUdpSocket::readyRead, this, &UdpServer::readPendingDatagrams); // 通讯
    connect(timer_, &QTimer::timeout, this, &UdpServer::udpTimeOut); // 定时器发送桌面数据, udp方式
    timer_->start(5000);
}

UdpServer::~UdpServer()
{
}

// 通讯
void UdpServer::readPendingDatagrams()
{
    //返回第一个挂起的UDP数据报的大小。如果没有可用的数据报，该函数返回-1。
    while (socket_->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket_->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket_->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort); // 读数据, 保存发送方的主机地址和端口
        processTheDatagram(datagram);
    }
}

// 解析读出来的数据
void UdpServer::processTheDatagram(QByteArray& data)
{
    if (data.length() >= 3)
    {
        // 读出来的数据长度大于3
        int offset = 1;
        char header;
        char tail;
        // 消息头header
        QByteArray intbytes = data.left(offset);
        memcpy(&header, intbytes.data(), intbytes.size());
        // 尾消息tail
        intbytes = data.right(1);
        memcpy(&tail, intbytes.data(), intbytes.size());
        //判断
        if (header == 'H' && tail == 'T')
        {
            // type
            char type;
            intbytes = data.mid(offset, 1);
            memcpy(&type, intbytes.data(), intbytes.size());
            offset += 1;
            if (type == 'L')//鼠标操作
            {
                //isLocker
                char isLocker;
                intbytes = data.mid(offset, 1); //pos, len
                memcpy(&isLocker, intbytes.data(), intbytes.size());
                //
                offset += 1;
                if (isLocker == 'Y')
                {
                    // 锁定鼠标
                    emit lockMouseSignal(true);  // 发出信号
                }
                else if (isLocker == 'N')
                {
                    // 解锁鼠标
                    emit lockMouseSignal(false);
                }
            }
            else if (type == 'R')
            {
            }
        }
    }
}

// 发送  ZX
void UdpServer::udpTimeOut()
{
    if (socket_)
    {
        QByteArray data;
        data.append("ZX");
        socket_->writeDatagram(data, QHostAddress::Broadcast, UDP_CLIENT_PORT);//光播, 发数据, 将大小为data的数据报发送到端口的主机地址
    }
}
