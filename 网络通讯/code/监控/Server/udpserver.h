#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class UdpServer : public QObject
{
    Q_OBJECT

public:
    UdpServer(QObject* parent = NULL);
    ~UdpServer();

signals:
    void lockMouseSignal(bool isLock);

private slots:
    void udpTimeOut();
    void readPendingDatagrams();

private:
    void processTheDatagram(QByteArray& datagram);

private:
    QUdpSocket* socket_;
    QTimer* timer_;
};

#endif // UDPSERVER_H
