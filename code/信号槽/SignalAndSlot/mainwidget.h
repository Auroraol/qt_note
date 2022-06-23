#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<subwidget.h>   //a自己添加的类在那用就要include

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QPushButton* btn;
    QPushButton b1;
    //a1
    QPushButton* b3;

 //1自定义槽函数
    void slotForwidget();

    void slotHideme(); // a4

    //创建一个子窗口对象
    Subwigdet subw;       //b2   // 创建一个子窗口对象 Subwidget: 就是封装了一个子窗口
    //  b 槽函数
    void slotshowme();    //b3
    void slotsubmsg(int num, QString str); //c

};

#endif // WIDGET_H

