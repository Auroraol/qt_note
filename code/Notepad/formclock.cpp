#include "formclock.h"
#include "ui_formclock.h"
#include <QTime>
#include <QTimer>

formClock::formClock(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::formClock)
{
    ui->setupUi(this);
    needleInint();
    QTimer* timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, [&]()
    {
        update();
    });
}


// 针初始化
void formClock::needleInint()
{
    //小时指针
    hourHand[0] = QPoint(3, 5);
    hourHand[1] = QPoint(0, 10);
    hourHand[2] = QPoint(-3, 5);
    hourHand[3] = QPoint(0, -50);
    //分钟指针
    minuteHand[0] = QPoint(3, 5);
    minuteHand[1] = QPoint(0, 12);
    minuteHand[2] = QPoint(-3, 5);
    minuteHand[3] = QPoint(0, -60);
    //秒钟指针
    secondHand[0] = QPoint(3, 5);
    secondHand[1] = QPoint(0, 14);
    secondHand[2] = QPoint(-3, 5);
    secondHand[3] = QPoint(0, -70);
}

// 绘制时针
void formClock::drawHourhand(QPainter* painter)
{
    painter->save();
    // 60分种时钟30度
    QTime time = QTime::currentTime();  //当前时间
    painter->rotate(30 * time.hour() + time.minute() * 0.5);
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawConvexPolygon(hourHand, 4);      // 绘制多边形
    painter->restore();
}

// 绘制分钟
void formClock::drawMinutehand(QPainter* painter)
{
    painter->save();
    QTime time = QTime::currentTime();  //当前时间
    painter->rotate(6 * time.minute() + time.second() * 0.1);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    painter->drawConvexPolygon(hourHand, 4);      // 绘制多边形
    painter->restore();
}

void formClock::drawSecondhand(QPainter* painter)
{
    painter->save();
    QTime time = QTime::currentTime();  //当前时间
    painter->rotate(6 * time.second()); // 一秒中6度
    painter->setBrush(Qt::green);
    painter->setPen(Qt::green);
    painter->drawConvexPolygon(hourHand, 4);      // 绘制多边形
    painter->restore();
}



// 绘制表盘
void formClock::drawClocDial(QPainter* painter)
{
    painter->save();
    //钟表刻度  // 每一个是6度
    for(int i = 1; i <= 60; i++)
    {
        painter->rotate(6);
        if (i % 5 == 0)    // 长刻度
        {
            painter->drawLine(0, -98, 0, -80);
            //painter->drawText(-20, -80, 40, 40, Qt::AlignHCenter | Qt::AlignTop, QString::number(i / 5));
        }
        else
        {
            painter->drawLine(0, -98, 0, -88);
        }
    }
    painter->restore();
    QFont font;
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(65 * qCos(qDegreesToRadians(0.0)), -65 * qSin(qDegreesToRadians(0.0)) + 5, "3");
    painter->drawText(65 * qCos(qDegreesToRadians(30.0)), -65 * qSin(qDegreesToRadians(30.0)), "2");
    painter->drawText(65 * qCos(qDegreesToRadians(60.0)), -65 * qSin(qDegreesToRadians(60.0)) + 1.5, "1");
    painter->drawText(65 * qCos(qDegreesToRadians(90.0)) - 10, -65 * qSin(qDegreesToRadians(90.0)), "12");
    painter->drawText(65 * qCos(qDegreesToRadians(120.0)) - 14, -65 * qSin(qDegreesToRadians(120.0)) + 1, "11");
    painter->drawText(65 * qCos(qDegreesToRadians(150.0)) - 11, -65 * qSin(qDegreesToRadians(150.0)) - 0.5, "10");
    painter->drawText(56 * qCos(qDegreesToRadians(180.0)) - 18, -65 * qSin(qDegreesToRadians(180.0)) + 5, "9");
    //
    painter->drawText(65 * qCos(qDegreesToRadians(210.0)) - 8, -65 * qSin(qDegreesToRadians(210.0)) + 10, "8");
    painter->drawText(65 * qCos(qDegreesToRadians(240.0)) - 5, -65 * qSin(qDegreesToRadians(240.0)) + 7, "7");
    painter->drawText(65 * qCos(qDegreesToRadians(270.0)) - 5, -65 * qSin(qDegreesToRadians(270.0)) + 10, "6");
    painter->drawText(65 * qCos(qDegreesToRadians(300.0)) + 2, -65 * qSin(qDegreesToRadians(300.0)) + 7, "5");
    painter->drawText(65 * qCos(qDegreesToRadians(330.0)) + 1, -65 * qSin(qDegreesToRadians(330.0)) + 10, "4");
}

formClock::~formClock()
{
    delete ui;
}

void formClock::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush(Qt::white, Qt::Dense3Pattern); // 颜色 画刷类型
    painter.setBrush(brush);
    painter.drawRect(0, 0, width(), height());
    // 动态缩放(自动匹配窗口大小)
    int side = qMin(width(), height() );  // 获取当前最小的值
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side); //设置矩形
    // 设置画家窗体
    painter.setWindow(0, 0, 200, 200);
    painter.translate(100, 100);
    // 绘制钟表盘
    drawClocDial(&painter);
    drawHourhand(&painter);
    drawMinutehand(&painter);
    drawSecondhand(&painter);
    // 绘制一个点
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0, 0), 3, 3);
}







/*
void formClock::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //设置画刷
    QBrush brush(Qt::white, Qt::Dense3Pattern); // 颜色 画刷类型
    painter.setBrush(brush);
    painter.drawRect(0, 0, width(), height());
    painter.drawRect(300, 300, 50, 80);
    painter.save();
    painter.translate(width() / 2, height() / 2);
    painter.drawEllipse(QPoint(0, 0), 100, 100);
    //  y : qCos(qDegreesToRadians(0.0))  // x: qsin()
    for(int i = 0; i < 12; i++)
    {
        painter.rotate(-29.7);  // 坐标系旋转30度
        painter.drawText(92, 0, "-");
    }
    painter.restore();
    painter.save();
    painter.translate(width() / 2, height() / 2);
    QFont font;
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(0, 0, ".");
    painter.drawText(100, 0, " 3");
    painter.drawText(-25, -105, " 12");
    painter.drawText(-125, 10, " 9");
    painter.drawText(-5, 115, " 6");
    painter.drawLine(0, 0, 90, 0);
    painter.restore();
}
*/


