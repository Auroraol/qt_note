#ifndef FORMCLOCK_H
#define FORMCLOCK_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QPoint>
#include <QPaintEvent>

namespace Ui
{
    class formClock;
}

class formClock : public QWidget
{
    Q_OBJECT

public:
    explicit formClock(QWidget* parent = 0);
    void drawClocDial(QPainter* painter);    // 绘制钟表
    void needleInint(); // 初始画针
    void drawHourhand(QPainter* painter);
    void drawMinutehand(QPainter* painter);
    void drawSecondhand(QPainter* painter);
    ~formClock();

private:
    Ui::formClock* ui;
    QPoint hourHand[4];    //小时指针
    QPoint minuteHand[4];  //分钟指针
    QPoint secondHand[4];  //秒钟指针

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // FORMCLOCK_H
