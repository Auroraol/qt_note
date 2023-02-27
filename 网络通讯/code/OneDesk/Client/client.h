#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include "agreement/method.h"
#include "picthread.h"


class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget* parent = nullptr);
    ~Client();

private slots:
    void sendData();
private:
    QTcpSocket* clientSocket;    // 客户端的套接字
    void loadSettings();
    void startPassiveConnect();
    Method method;
    QTimer* timer;
    // PicThread* picThread;
    void startTransfer();
    QImage CatchScreen();
    QByteArray getImageData(const QImage& image);


    //

    QByteArray outBlock;  // 数据缓冲区，即存放每次要发送的数据块
    qint64 totalBytes;    // 发送数据的总大小
};
#endif // CLIENT_H
