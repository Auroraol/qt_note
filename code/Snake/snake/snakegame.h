#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "food.h"
#include "snake.h"
#include <QPaintEvent>
#include <QPixmap>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class SnakeGame;
}
QT_END_NAMESPACE

class SnakeGame : public QWidget
{
    Q_OBJECT

public:
    SnakeGame(QWidget* parent = nullptr);
    ~SnakeGame();


private slots:
    void on_pushButton_p_clicked();

    void on_updateFood_clicked();

    void on_pushButton_S_clicked();

private:
    Ui::SnakeGame* ui;
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);
    Food* m_food;
    Snake* m_snake;
    QPixmap* m_pPixmap;
    QPainter* m_pPainter;
    QTimer* m_time;
    bool isRotate;
    int score;
    bool flag;
    void initMap();
    bool GameOver();
    void EatFood();
};
#endif // SNAKEGAME_H
