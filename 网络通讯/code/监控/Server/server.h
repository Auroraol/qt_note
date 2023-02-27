#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject* parent = NULL);
    ~Server();

    void setAutoStart();
    void stopAutoStart();
    bool GetIsAutoStart();

private:
    QTcpServer* server_;
    QMap<QString, QTcpSocket*> clientMap_;

    QTimer* timer_;
    bool isLockMouse_;
    quint64 lockTimes_;  //  ��������ʱ��

private:
    //�������
    void lockMouse();


public slots :
    void clinetConnected();
    void clientIncomingMsg();
    void removeClient();
    void sendData();

    void lockerMouseSlot(bool isLock);
};

#endif // SERVER_H
