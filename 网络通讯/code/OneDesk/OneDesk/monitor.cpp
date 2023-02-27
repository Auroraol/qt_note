#include "monitor.h"
#include "ui_monitor.h"


Monitor::Monitor(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);
    imageSize = 0;
    totalBytes = 0;
    bytesReceived = 0;
}
Monitor::~Monitor()
{
    delete ui;
}

void Monitor::setCurrSocket(QTcpSocket* socket)
{
    m_connctionSocket = socket;
    m_connctionSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1); //尝试优化套接字以降低延迟
    QString str = QString("%1  %2").
                  arg(m_connctionSocket->peerAddress().toString()).
                  arg(QString::number(m_connctionSocket->peerPort()));
    setWindowTitle(str);
    if (m_connctionSocket != NULL )
    {
        // 发起开始监控命令
        method.sendStr(m_connctionSocket, "CLIENT_START_MONITOR", CLIENT_START_MONITOR);
        // 通讯
        connect(m_connctionSocket, &QTcpSocket::readyRead, this, &Monitor::onReadyRead);
    }
}

// 服务器接收数据
void Monitor::onReadyRead()
{
    //接收:  接收桌面数据,显示在弹出中
    QPixmap pixmap;
    method.readMsg(m_connctionSocket, NULL, &pixmap);
    if (!pixmap.isNull())
    {
        showPixmap(&pixmap);
    }
}


void Monitor::showPixmap(QPixmap* pixmap)
{
    pixmap->scaled(ui->label->size(), Qt::IgnoreAspectRatio);//重新调整图像大小以适应窗口
    pixmap->scaled(ui->label->size(), Qt::KeepAspectRatio);//设置pixmap缩放的尺寸
    ui->label->setScaledContents(true);                 //设置label的属性,能够缩放pixmap充满整个可用的空间。
    ui->label->setPixmap(*pixmap);
}

