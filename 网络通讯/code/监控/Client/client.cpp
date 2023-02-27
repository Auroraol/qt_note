#include "client.h"
#include "ui_client.h"
#include <QMessagebox>
#include <QHostAddress>
#include <QDir>

#define SERVER_PORT 44444
#define UDP_CLIENT_PORT 44448
#define UDP_SERVER_PORT 44446

Client::Client(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Client)
    , timer_(new QTimer(this))
{
    ui->setupUi(this);
    isConnected_ = false;
    isRecord_ = false;
    socket_ = new QTcpSocket(); //tcp
    socket_->setSocketOption(QAbstractSocket::LowDelayOption, 1); //尝试优化套接字以降低延迟
    connect(socket_, &QTcpSocket::readyRead, this, &Client::readFortune); // tcp通讯
    connect(socket_, &QTcpSocket::stateChanged, this, &Client::handerStateChanged);  // 状态改变
    connect(socket_, &QAbstractSocket::errorOccurred, this, &Client::handerSockcteErrorr);  // 错误处理
    udpSocket_ = new QUdpSocket(this); // udp
    udpSocket_->bind(UDP_CLIENT_PORT, QUdpSocket::ShareAddress); //绑定自己端口号
    connect(udpSocket_, &QUdpSocket::readyRead, this, &Client::readPendingDatagrams); // udp通讯
    connect(timer_, &QTimer::timeout, this, &Client::serverTimeOut); // 定时器. 检测服务器
    timer_->start(5000);
    ui->lineEdit_ip->setText("192.168.");
    showMaximized();  // 窗口最大化
}

Client::~Client()
{
    delete ui;
}

// 连接服务器
void Client::connectServer(QString ip)
{
    socket_->abort(); //终止当前连接并重置套接字。与 disconnectFromHost()不同，该函数立即关闭套接字，去弃写入缓冲区中的任何挂起数据
    receiveData_.clear(); //清空接受的数据
    socket_->connectToHost(QHostAddress(ip), SERVER_PORT); // 建立链接
    ui->lineEdit_ip->setText(ip);
}

// tcp通讯
// 读出数据
void Client::readFortune()
{
    quint64 bytesAvailable = socket_->bytesAvailable();  // 返回socket_得到的数据
    if (bytesAvailable <= 0)
    {
        return;
    }
    QByteArray data = socket_->read(bytesAvailable); //读出数据
    //qDebug() << "from:" << socket_->peerAddress().toString() << " size:" << data.size();
    receiveData_.append(data);
    processData();
}


// 处理连接错误
void Client::handerSockcteErrorr(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("没有找到服务器。请查看主机名和端口设置"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The connection was refused by the peer. "
                                        "Make sure the fortune server is running, "
                                        "and check that the host name and port "
                                        "settings are correct."));
            break;
        default:
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The following error occurred: %1.")
                                     .arg(socket_->errorString()));
    }
}

// 处理连接状态
void Client::handerStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::HostLookupState:
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            isConnected_ = true;
            break;
        case QAbstractSocket::BoundState:
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
        case QAbstractSocket::UnconnectedState:
            {
                isConnected_ = false;
                isRecord_ = false;
                ui->pushButton_record->setText(QString::fromLocal8Bit("录像"));
                break;
            }
        default:
            Q_ASSERT_X(0, "stateChanged", "Unknown socket state!");
    }
}


// 解析tcp读出来的数据(读到的是图片)
void Client::processData()
{
    int headerLength = sizeof(quint64) + 2;  //10个字节 [图片大小 消息头]的大小
    while (true)
    {
        // 如果接收到的数据小于[图片大小 消息头]的大小, 不读取
        if (receiveData_.size() <= headerLength)
        {
            return;
        }
        int totalLenth = receiveData_.length();
        // 判断得到的消息头是HT
        if (receiveData_.at(0) == 'H' && receiveData_.at(1) == 'T')
        {
            //得到图片大小
            int dataLength = 0;
            QByteArray intbytes = receiveData_.mid(2, sizeof(quint64)); //
            memcpy(&(dataLength), intbytes.data(), intbytes.size());
            // 图片
            if (totalLenth > headerLength + dataLength)
            {
                QByteArray picData = receiveData_.mid(headerLength, dataLength);
                showPic_.loadFromData(picData); //从QByteArray中加载
                showPixmap(&showPic_);
                receiveData_.remove(0, headerLength + dataLength);
            }
            //qDebug() << "left length:" << receiveData_.length();
            return;
        }
        else
        {
            receiveData_.remove(0, 1);
            qDebug() << "remove ";
        }
    }
}

//显示图像
void Client::showPixmap(QPixmap* pixmap)
{
    pixmap->scaled(ui->label_show->size(), Qt::IgnoreAspectRatio); //重新调整图像大小以适应窗口
    pixmap->scaled(ui->label_show->size(), Qt::KeepAspectRatio);  //设置pixmap缩放的尺寸
    ui->label_show->setScaledContents(true);                      //设置label的属性,能够缩放pixmap充满整个可用的空间。
    ui->label_show->setPixmap(*pixmap);
}


// udp通讯
void Client::readPendingDatagrams()
{
    //返回第一个挂起的UDP数据报的大小。如果没有可用的数据报，该函数返回-1。
    while (udpSocket_->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket_->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket_->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort); // 读数据, 并保存发送方的主机地址和端口
        QString ip = formatIP(sender.toString());     // 转成10进制形式
        processTheDatagram(datagram, ip, senderPort);
    }
}

// 解析udp读出来的数据(读的是消息头ZX)
void Client::processTheDatagram(QByteArray& datagram, QString ip, quint32 port)
{
    if (datagram.length() >= 2)
    {
        QByteArray midData = datagram.mid(0, 2);
        if (QString(midData).compare("ZX") == 0)
        {
            if (!serverIpMap_.contains(ip))
            {
                setList(); //列表显示
            }
            serverIpMap_[ip] = QDateTime::currentDateTime();  //当前时间
        }
    }
}

// ip地址转成10进制形式
QString Client::formatIP(QString ip)
{
    QString str;
    if (ip.contains(":"))
    {
        QStringList tmpList = ip.split(":");
        foreach(QString tmp, tmpList)
        {
            if (tmp.contains("."))
            {
                str = tmp;
                break;
            }
        }
    }
    else
    {
        str = ip;
    }
    return str;
}

// 服务器关闭与否
void Client::serverTimeOut()
{
    QStringList ips = serverIpMap_.keys(); // 服务器ip地址
    QDateTime curT = QDateTime::currentDateTime();
    foreach(QString ip, ips)
    {
        if (serverIpMap_[ip].secsTo(curT) > 20)
        {
            // 大于20s,剔除
            serverIpMap_.remove(ip);
        }
    }
    setList();
}


//  ui->listWidget列表显示
void Client::setList()
{
    ui->listWidget->clear();
    if (serverIpMap_.size() > 0)
    {
        ui->listWidget->addItems(serverIpMap_.keys());
    }
}


void Client::on_listWidget_doubleClicked(const QModelIndex& index)
{
    if (!index.isValid())  //如果索引有效
    {
        return;
    }
    QString ip = ui->listWidget->item(index.row())->data(0).toString(); // 读出服务器ip
    connectServer(ip); //连接
}

// 点击连接按钮
void Client::on_pushButton_connect_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    if (ip.split(".").size() != 4)
    {
        QMessageBox::information(NULL, "警告", "ip格式错误");
        return;
    }
    connectServer(ip);
}


void Client::on_pushButton_record_clicked()
{
    if (isRecord_)
    {
        ui->pushButton_record->setText(QString::fromLocal8Bit("录像"));
        isRecord_ = false;
    }
    else
    {
        if (isConnected_)
        {
            isRecord_ = true;
            ui->pushButton_record->setText(QString::fromLocal8Bit("停止录像"));
        }
    }
}


void Client::on_pushButton_playback_clicked()
{
}


void Client::on_pushButton_getpic_clicked()
{
    if (!isConnected_)
    {
        return;
    }
    QString ip = ui->lineEdit_ip->text();
    QString path = QApplication::applicationDirPath();
    path += tr("/pic/");
    QDir dir(path);
    if (!dir.exists())
    {
        if (!(dir.mkdir(path)))
        {
            path == QString("C:\\");
        }
    }
    QString fileName = path + ip + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss") + ".bmp";
    bool isok = showPic_.save(fileName);
    if (isok)
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("截图提示"), QString::fromLocal8Bit("保存成功\n%1").arg(fileName));
    }
}

// udp发送数据 --> 鼠标锁定, 鼠标解锁, 回放, 录屏, 截屏消息
void Client::on_pushButton_lock_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    QByteArray message;
    QByteArray intbytes;
    //set header
    message.append('H');
    //set type
    message.append('L');
    //set is lock
    message.append('Y');
    //set tail
    message.append('T');
    udpSendData(ip, message);
}

void Client::on_pushButton_unlock_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    QByteArray message;
    QByteArray intbytes;
    //set header
    message.append('H');
    //set type
    message.append('L');
    //set is lock
    message.append('N');
    //set tail
    message.append('T');
    udpSendData(ip, message);
}

void Client::udpSendData(QString ip, const QByteArray& data)
{
    udpSocket_->writeDatagram(data, QHostAddress(ip), UDP_SERVER_PORT);
}














