#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 动态对象
    mc1 = new MyClass1(this);
    mc2 = new MyClass2(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::close);  // 系统自带

    //connect(信号发出者, 发出的信号, this, 处理信号的槽函数);
    // 信号发出者-->mc1
    // 信号处理者-->mc2
    connect(mc1, &MyClass1::MySignal, mc2, &MyClass2::MySlot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()   // 通过ui界面的添加槽自动添加的
{
    //qDebug() << "You have just clicked the button";
    emit mc1->MySignal(num++);
}
