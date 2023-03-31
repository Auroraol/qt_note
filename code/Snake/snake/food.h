#ifndef FOOD_H
#define FOOD_H

#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <vector>

using namespace std;

class Food
{
public:
    explicit Food(int n);
    void DrawFood(QPainter& p);
    void updatePos();
    vector<QPoint> GetFoodPos();
    void updatePos(QPoint pos);
private:
    vector<QPoint> foodPos;
    int number;

signals:

};

#endif // FOOD_H
