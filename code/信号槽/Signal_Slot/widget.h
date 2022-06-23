#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myclass1.h"     // 导入 myclass的头文件
#include "myclass2.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_2_clicked();   // 槽函数

private:
    Ui::Widget *ui;
    // 类的对象
    MyClass1 *mc1;
    MyClass2 *mc2;

    int num = 1;
};

#endif // WIDGET_H
