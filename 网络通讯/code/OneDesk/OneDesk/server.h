#ifndef SERVER_H
#define SERVER_H

#include "monitor.h"
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTableWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class Server;
}
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget* parent = nullptr);
    ~Server();


private slots:
    void on_pushButton_open_clicked();
    void on_pushButton_close_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem* item);
    void on_tableWidget_customContextMenuRequested(const QPoint& pos);
    void actionTriggered(QAction* action);
    void clinetConnected();
    void removeClient();


private:
    Ui::Server* ui;
    QTcpServer* m_server;
    QMap<QString, QTcpSocket*> m_clientMap;
    Monitor* monitorWindow;
    void showInfoTabl();
    void initTableWidget();
};
#endif // SERVER_H
