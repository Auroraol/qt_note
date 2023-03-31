#include "snake.h"
#include "configure.h"

#include <QDebug>

Snake::Snake()
{
    QPoint p;
    for (int i = 0; i < SNAKESIZ; i++)
    {
        p.setX(SNAKE_W * i);
        p.setY(0);
        lSnake.push_back(p);
    }
    dir = Snake::Right;
    bIsSuccess = true;
}

void Snake::DrawSnake(QPainter& p)
{
    for (auto pos : lSnake)
    {
        QColor qc = QColor::fromHsl(rand() % 360, rand() % 256, rand() % 200);
        QRect rect(pos.x(),  pos.y(), SNAKE_W, SNAKE_H);
        p.fillRect(rect, qc);
    }
}

void Snake::MoveSnake()
{
    //处理后面
    list<QPoint> tempList;
    bool flag = false;
    for (auto pos : lSnake)
    {
        if (flag)
        {
            tempList.push_back(pos);
        }
        flag = true;
    }
    QPoint pos = lSnake.back();
    lSnake.swap(tempList);
    lSnake.push_back(pos);
    //处理蛇头
    switch (dir)
    {
        case Snake::Right:
            {
                QPoint posr = lSnake.back();
                posr.rx() += SNAKE_W;
                lSnake.pop_back();
                lSnake.push_back(posr);
                break;
            }
        case Snake::Left:
            {
                QPoint posl = lSnake.back();
                posl.rx() -= SNAKE_W;
                lSnake.pop_back();
                lSnake.push_back(posl);
                break;
            }
        case Snake::Up:
            {
                QPoint posu = lSnake.back();
                posu.ry() -= SNAKE_W;
                lSnake.pop_back();
                lSnake.push_back(posu);
                break;
            }
        case Snake::Down:
            {
                QPoint posd = lSnake.back();
                posd.ry() += SNAKE_W;
                lSnake.pop_back();
                lSnake.push_back(posd);
                break;
            }
    }
    QPoint snakeHead = lSnake.back();
    int x1 = snakeHead.x();
    int y1 = snakeHead.y();
    //蛇尾
    QPoint snakeTail  = lSnake.front();
    int x2 = snakeTail.x();
    int y2 = snakeTail.y();
    if (x2 == x1 && y2 == y1)
    {
        bIsSuccess = false;
    }
}

QPoint Snake::GetSnakeHeadPos( )
{
    return lSnake.back();
}


