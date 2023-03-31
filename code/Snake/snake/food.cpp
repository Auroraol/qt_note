#include "food.h"
#include "configure.h"

Food::Food(int n)
{
    number = n;
    QPoint pos;
    while (foodPos.size() < number)
    {
        pos.rx() = rand() % (WINDOW_W / SNAKE_W) * SNAKE_W;  //  保证是SNAKE_W的整数倍并且再WINDOW_W范围里
        pos.ry() = rand() % (WINDOW_H / SNAKE_H) * SNAKE_W;  //  保证和蛇头对齐
        vector<QPoint>::iterator it = std::find(foodPos.begin(), foodPos.end(), pos);
        if(it == foodPos.end())
        {
            foodPos.push_back(pos);
        }
    }
}

void Food::DrawFood(QPainter& p)
{
    for (auto pos : foodPos)
    {
        QColor qc = QColor::fromHsl(rand() % 360, rand() % 256, rand() % 200);
        QRect rect(pos.x(),  pos.y(), SNAKE_W, SNAKE_H);
        p.fillRect(rect, qc);
    }
}
void Food::updatePos(QPoint pos)
{
    for(vector<QPoint>::iterator iter = foodPos.begin(); iter != foodPos.end(); iter++)
    {
        //从vector中删除指定的某一个元素
        if(*iter == pos)
        {
            foodPos.erase(iter);
            break;
        }
    }
}
vector<QPoint> Food::GetFoodPos()
{
    return foodPos;
}
