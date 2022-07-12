#include "widget.h"
#include "ui_widget.h"
#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //显示文字
    ui->label->setText("I love you Rick!");
    //显示图片
    ui->label_2->setPixmap(QPixmap(":/Image/Image/1.jpeg"));
    ui->label_2->setScaledContents(true);   // 缩放
    //显示动图
    QMovie *mv = new QMovie(":/Image/Image/2.gif");
    ui->label_3->setMovie(mv);
    ui->label_3->setScaledContents(true);  // 缩放
    mv->start();
}

Widget::~Widget()
{
    delete ui;
}
