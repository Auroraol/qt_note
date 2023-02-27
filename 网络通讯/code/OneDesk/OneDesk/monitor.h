#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include "agreement/method.h"

namespace Ui
{
    class Monitor;
}

class Monitor : public QWidget
{
    Q_OBJECT

public:
    explicit Monitor(QWidget* parent = nullptr);
    ~Monitor();

    void setCurrSocket(QTcpSocket* socket);
private slots:
    void onReadyRead();
private:
    Ui::Monitor* ui;
    QTcpSocket* m_connctionSocket = NULL;  // 通讯套接字
    Method method;
    void showPixmap(QPixmap* pixmap);
    void updateServerProgress();

    qint64 totalBytes;     // 存放总大小信息
    qint64 bytesReceived;  // 已收到数据的大小
    qint64 fileNameSize;   // 文件名的大小信息
    qint64 imageSize; //图片大小
    QString imageContent;
    QImage getImage(const QString& data);

    //
    QPixmap showPic_;
    QByteArray receiveData_;
};

#endif // MONITOR_H
