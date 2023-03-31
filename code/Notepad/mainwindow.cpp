#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QLabel>
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QByteArray>
#include <QMouseEvent>
#include <QFontDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QCloseEvent>
#include <QColorDialog>

#include <QMenu>


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainInit();
    addtray();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainInit()
{
    this->setWindowTitle("记事本");
    this->setWindowIcon(QIcon(":/res/images/图标.png"));
    this->setStyleSheet("#MainWindow{background-image:url(:/res/images/背景.jpg);}");
    ui->textEdit->setStyleSheet("background-color: rgb(87,97,105);");
    resize(1156, 876);
    //设置默认输入字体大小
    ui->textEdit->setFont(QFont("宋体", 16));
    ui->textEdit->setTextColor(Qt::white);
    statusBarInit();
    connect(ui->textEdit, &QTextEdit::textChanged, this, [ = ]()
    {
        //  判断是否修改
        if (ui->textEdit->document()->isModified())
        {
            setWindowTitle(strWindowTitle + "*");  // 修改了在标题上再都显示一个 *
        }
    });
    flag = false;
    flagTray = false;
}

void MainWindow::statusBarInit()
{
    //ui->statusBar->setStyleSheet("background-color: rgb(236,233,216);");//更改背景颜色rgb(236,233,216)
    ui->statusBar->setStyleSheet("background-color: rgb(224,223,227);");
    //临时消息
    ui->statusBar->showMessage("欢迎使用记事本");
    //长久消息
    QLabel* info1 = new QLabel(this);
    info1->setFrameStyle(QFrame::Box | QFrame::Sunken);
    info1->setText("金刀");
    ui->statusBar->addPermanentWidget(info1);
    QLabel* info2 = new QLabel(this);
    info2->setFrameStyle(QFrame::Box | QFrame::Sunken);  // 有个边框
    QDateTime nowtime = QDateTime::currentDateTime();
    QString currnt = nowtime.toString("yyyy.MM.dd hh:mm:ss");
    qDebug() << currnt;
    info2->setText(currnt);
    ui->statusBar->addPermanentWidget(info2);   // 放在右边
}

// 打开文本文件
void MainWindow::on_action_open_triggered()
{
    QString fileName =  QFileDialog::getOpenFileName(this, "打开文件", "C:/Users/16658/Desktop", "文本文件(*.txt);; 所有文件(*.*)");
    if (fileName.isEmpty())
    {
        return;
    }
    // 文件读写
    QFile file(fileName);
    // 读
    bool isOpen = file.open(QFile::ReadOnly);
    if (!isOpen)
    {
        QMessageBox::warning(this, "警告", "打开文件失败");
        return;
    }
    QString strContent =  file.readAll();
    // 关闭文件
    file.close();
    filePath = fileName;
    // 显示到界面
    ui->textEdit->setText(strContent);
    QFileInfo fileInfo(fileName);
    strWindowTitle = fileInfo.fileName();
    this->setWindowTitle(strWindowTitle);
}

void MainWindow::wheelEvent(QWheelEvent* ev)
{
    if (ev->modifiers() == Qt::ControlModifier && ev->delta() > 0)
    {
        ui->textEdit->zoomIn();  // 向上滚放大
    }
    else if(ev->modifiers() == Qt::ControlModifier && ev->delta() < 0)
    {
        ui->textEdit->zoomOut();
    }
}

void MainWindow::closeEvent(QCloseEvent* ev)
{
    qDebug() << "closeEvent ";
    if (!filePath.isEmpty() && ev->type() == QEvent::Close)
    {
        result = QMessageBox::information(this, "记事本", "您的文本已经改变了,是否保存?", QMessageBox::Yes, QMessageBox::No);
        if (result == QMessageBox::Yes)
        {
            //保存 //保存到原位置
            on_actions_save_triggered();
            //满足条件 不退出
            ev->ignore();
        }
    }
    qDebug() << "closeEvent ";
}

// 字体对话框
void MainWindow::on_action_front_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("宋体", 16), this);
    if (ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        qDebug() << "没有选择任何字体";
    }
}

//撤销
void MainWindow::on_action_undo_triggered()
{
    ui->textEdit->undo();
}

// 剪切
void MainWindow::on_actions_cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_action_ause_triggered()
{
    ui->textEdit->paste();
}

// 删除所在行
void MainWindow::on_action_delete_triggered()
{
    QTextCursor txtcur = ui->textEdit->textCursor();
    txtcur.select(QTextCursor::BlockUnderCursor);
    txtcur.removeSelectedText();
}

void MainWindow::on_actions_all_triggered()
{
    ui->textEdit->selectAll();
}

// 保存文本文件
void MainWindow::on_actions_save_triggered()
{
    //  判断是否修改
    if (filePath.isEmpty())
    {
        // 另存为
        on_actionss_3_triggered();
    }
    else
    {
        // 读取textedit上面的所有文件
        QString curContent =  ui->textEdit->toPlainText();
        // 写
        QFile file(filePath);
        bool is_ok =  file.open(QFile::WriteOnly);
        if (!is_ok)
        {
            QMessageBox::warning(this, "警告", "打开写入失败");
            return;
        }
        QTextStream ts(&file);
        ts << curContent;
        file.close();
    }
    // 改变标题去掉星号
    QFileInfo fileInfo(filePath);
    strWindowTitle = fileInfo.fileName();
    this->setWindowTitle(strWindowTitle);
    // 修改标记 // 防止退出的时候还是弹出提示对话框
    ui->textEdit->document()->setModified(false);
}

// 退出
void MainWindow::on_actionss_x_triggered()
{
    //  判断是否修改
    if (ui->textEdit->document()->isModified())
    {
        result = QMessageBox::information(this, "记事本", "您的文本已经改变了,是否保存?", QMessageBox::Yes, QMessageBox::No);
        if (result == QMessageBox::Yes)
        {
            //保存 //保存到原位置
            on_actions_save_triggered();
        }
        else if (result == QMessageBox::No)
        {
            //退出
            close();
        }
    }
}

// 另存为
void MainWindow::on_actionss_3_triggered()
{
    QString newFilePath = QFileDialog::getSaveFileName(this, "文件另存为", "C:/Users/16658/Desktop", "所有文件(*.*)");
    filePath = newFilePath;
    // 保存
    if (!filePath.isEmpty())
    {
        on_actions_save_triggered();
    }
}

// 新建
void MainWindow::on_action_n_triggered()
{
    int res = QMessageBox::question(this, "提示", "新建文本, 是否保存当前文本?", QMessageBox::Yes, QMessageBox::No);
    if (res == QMessageBox::Yes)
    {
        on_actions_save_triggered();
    }
    ui->textEdit->clear();
}

// 日历
void MainWindow::on_action_date_triggered()
{
    if (!flag)
    {
        ui->stackedWidget->setCurrentIndex(1);
        flag = true;
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        flag = false;
    }
}


void MainWindow::on_actionsdjgj_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->textEdit->setTextColor(color);
}

void MainWindow::on_action_about_triggered()
{
    QString str = QString("%1").arg("Copyright c 2022-2099 JinDao");
    QMessageBox::about(this, "Briefness Text", str);
}

void MainWindow::on_showBackground_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}


QSystemTrayIcon tray; //任务栏托盘角标
// 系统托盘
void MainWindow::addtray()
{
    tray.setToolTip("记事本");
    tray.setIcon(QIcon(":/res/images/图标.png"));
    QMenu* menu = new QMenu();
    action_showDialog = new QAction("显示主窗口");
    action_exit = new QAction("退出");
    menu->addAction(action_showDialog);//添加菜单
    menu->addAction(action_exit);//添加菜单
    tray.setContextMenu(menu);//绑定菜单
    //绑定托盘小图标点击事件
    connect(&tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(OnSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
    //绑定菜单点击事件
//    connect(action_showDialog, &QAction::triggered, this, &MainWindow::onShowDialogClick);
    connect(action_exit, &QAction::triggered, this, &MainWindow::on_exitButton_clicked);
    tray.show(); //显示小图标
}

//点击“打开主窗口”时显示窗口
//点击了任务栏托盘小图标
void MainWindow::OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        if (flagTray == false)
        {
            Qt::WindowFlags m_flags = windowFlags();
            setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
            this->showNormal();//如果点击了任务栏托盘小图标，则显示本窗口
            flagTray = true;
        }
        else
        {
            this->hide();
            flagTray = false;
        }
    }
}
//“退出”时相当于点击主窗口里面的“退出”按钮，所以直接绑定到“退出”按钮的点击事件
//退出按钮点击事件，同时任务栏小图标的”退出“菜单也会执行这个函数
void MainWindow::on_exitButton_clicked()
{
    this->hide();//隐藏窗口
//    WriteSetting();//写入设置
    qApp->exit(0);//退出
}
