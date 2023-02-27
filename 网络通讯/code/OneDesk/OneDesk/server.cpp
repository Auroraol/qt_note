#include "server.h"
#include "ui_server.h"


#include <QMenu>
#define SERVER_PORT 44444  //服务器端口号

Server::Server(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    initTableWidget();
    m_server = new QTcpServer();
    monitorWindow = new Monitor;
}

Server::~Server()
{
    delete ui;
}

// 开启服务器按钮
void Server::on_pushButton_open_clicked()
{
    if (m_server->listen(QHostAddress::Any, SERVER_PORT)) // 监听
    {
        qDebug() << QString::fromLocal8Bit("服务器开启") ;
        ui->label->setText("服务器已运行");
        connect(m_server, &QTcpServer::newConnection, this, &Server::clinetConnected);
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("服务器开启失败") << m_server->errorString();
    }
}

//新增客户端
void Server::clinetConnected()
{
    QTcpSocket* camera = m_server->nextPendingConnection(); // 获取通讯套接字
    QString ip = camera->peerAddress().toString();
    QString port = QString().setNum(camera->peerPort());
    QString clientName = ip + ":" + port;
    // 使用hash表保存通讯套接字
    m_clientMap[clientName] = camera;  //QMap<QString, QTcpSocket*> clientMap_;
    qDebug() << "新增客户端: " << clientName << "当前客户端个数:" << m_clientMap.size();
    connect(camera, &QTcpSocket::disconnected, this, &Server::removeClient);  // 通讯套接字没有连接服务器就断开
    //
    showInfoTabl();
    // 通讯
}

//移除客户端
void Server::removeClient()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    QString ip = client->peerAddress().toString();
    QString port = QString().setNum(client->peerPort());
    QString cameraName = ip + ":" + port;
    if (m_clientMap.contains(cameraName))
    {
        m_clientMap.remove(cameraName);
    }
    qDebug() << "移除客户端: " << cameraName << "当前客户端个数:" << m_clientMap.size();
    //
    showInfoTabl();
    monitorWindow->close();
}

// 关闭服务器按钮
void Server::on_pushButton_close_clicked()
{
    ui->label->setText("服务器未运行");
    m_server->close();
    QMap<QString, QTcpSocket*>::iterator it = m_clientMap.begin();
    while(it != m_clientMap.end())
    {
        //主动和客户端断开连接
        it.value()->disconnectFromHost();  //断开连接
        it.value()->close();
        it++;
    }
}

// 初始化表格
void Server::initTableWidget()
{
    ui->tableWidget->setColumnCount(1);
    QStringList list;
    list << "监控列表";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

// 显示表格
void Server::showInfoTabl()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    // 依次追加, 显示客户端信息[ip, port]
    QMap<QString, QTcpSocket*>::iterator it = m_clientMap.begin();
    while(it != m_clientMap.end())
    {
        int n = ui->tableWidget->rowCount();
        //qDebug() << n;
        ui->tableWidget->insertRow(n);
        ui->tableWidget->setItem(n, 0, new QTableWidgetItem(it.key()));
        it++;
    }
}


// 双击打开监控窗口
void Server::on_tableWidget_itemDoubleClicked(QTableWidgetItem* item)
{
    if (m_clientMap.contains(item->text()))
    {
        // 传递当前点击的客户端的套接字
        monitorWindow->setCurrSocket(m_clientMap[item->text()]);
        if(monitorWindow->isHidden())  // 如果隐藏了就显示
        {
            monitorWindow->show();
        }
        else
        {
            monitorWindow->hide();
        }
    }
}
// tableWidget右键菜单  //TODO
void Server::on_tableWidget_customContextMenuRequested(const QPoint& pos)
{
    QMenu menu;
    QAction* logout = menu.addAction(tr("注销"));
    menu.addSeparator();  //增加分割行
    QAction* reboot = menu.addAction(tr("重启"));
    menu.addSeparator();
    QAction* shutdown = menu.addAction(tr("关机"));
    menu.addSeparator();
    QAction* exitMonitor = menu.addAction(tr("退出监控端"));
    menu.addSeparator();
    QAction* autoStartup = menu.addAction(tr("开机自动启动"));
    connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(actionTriggered(QAction*)));
    menu.exec(QCursor::pos());
}
// TODO
void Server::actionTriggered(QAction* action)
{
//    if(action->text() == "注销")
//    {
//    }
//    else if(action->text() == "退出")
//    {
//        this->hide();
//        saveSettings();//写入设置
//        qApp->exit(0);
//    }
}
