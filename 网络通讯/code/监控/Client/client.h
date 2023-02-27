#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QMutex>
#include <QPixMap>
#include <QUdpSocket>
#include <QDateTime>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class Client;
}
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget* parent = nullptr);
    ~Client();

private:
    Ui::Client* ui;
    QTcpSocket* socket_;  // 通讯套接字

    bool isConnected_;

    QByteArray receiveData_;

    QPixmap showPic_;

    QUdpSocket* udpSocket_;

    QMap<QString, QDateTime> serverIpMap_;  // 服务器列表 [服务器ip, 连接的时间]

    QTimer* timer_;

    bool isRecord_;

    QTimer* timer;

private:
    void connectServer(QString ip);

    void processData();
    void processTheDatagram(QByteArray& datagram, QString ip, quint32 port);
    QString formatIP(QString ip);
    void setList();
    void udpSendData(QString ip, const QByteArray& data);
    void showPixmap(QPixmap* pixmap);




public slots:
    void readFortune();
    void handerSockcteErrorr(QAbstractSocket::SocketError socketError);
    void handerStateChanged(QAbstractSocket::SocketState socketState);
    void readPendingDatagrams();
    void serverTimeOut();



private slots:
    void on_pushButton_getpic_clicked();
    void on_pushButton_record_clicked();
    void on_pushButton_playback_clicked();
    void on_pushButton_lock_clicked();
    void on_pushButton_unlock_clicked();
    void on_pushButton_connect_clicked();
    void on_listWidget_doubleClicked(const QModelIndex& index);
};
#endif // CLIENT_H
