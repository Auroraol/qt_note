#ifndef SNAKE_H
#define SNAKE_H

#include "food.h"
#include <list>
#include <QPoint>
#include <QPainter>

using namespace std;

class Snake
{
public:
    Snake();
    void DrawSnake(QPainter& p);
    void MoveSnake();
    QPoint GetSnakeHeadPos();

public:
    int dir;					//蛇的方向
    enum DIR {Right, Left, Down, Up};
    list<QPoint> lSnake;
    bool bIsSuccess;                          //游戏是否成功

};

#endif // SNAKE_H
