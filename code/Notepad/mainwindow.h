#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    void mainInit();
    void statusBarInit();
    ~MainWindow();

protected:
    void wheelEvent(QWheelEvent* ev);
    void closeEvent(QCloseEvent* ev);

private slots:
    void on_action_open_triggered();  // 打开文件
    void on_action_front_triggered();  // 设置字体
    void on_action_undo_triggered(); // 撤销
    void on_actions_cut_triggered();
    void on_action_copy_triggered();
    void on_action_ause_triggered();
    void on_action_delete_triggered();
    void on_actions_all_triggered();
    void on_actions_save_triggered();
    void on_actionss_x_triggered();
    void on_actionss_3_triggered();
    void on_action_n_triggered();
    void on_action_date_triggered();
    void on_actionsdjgj_triggered();
    void on_action_about_triggered();
    void on_showBackground_triggered();
    void addtray();//  系统托盘
    void on_exitButton_clicked();
    void OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason);


private:
    Ui::MainWindow* ui;
    QString strWindowTitle;
    QString filePath;
    int result;
    bool flag;
    QAction* action_showDialog;
    QAction* action_exit;
    bool flagTray;
};

#endif // MAINWINDOW_H
