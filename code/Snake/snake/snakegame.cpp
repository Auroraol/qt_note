#include "snakegame.h"
#include "ui_snakegame.h"
#include "configure.h"
#include <QDebug>
#include <Qtimer>
#include <algorithm>

SnakeGame::SnakeGame(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SnakeGame)
    , m_snake(new Snake)
    , m_pPixmap(new QPixmap(WINDOW_W, WINDOW_H))  // 画纸大小
    , m_pPainter(new QPainter)
    , isRotate(false)
    , score(0)
    , flag(false)
{
    ui->setupUi(this);
    setFocus(); //  键盘焦点将会即时转移到该小部件下
    setFixedSize(WINDOW_W + 200, WINDOW_H);
    ui->isRun->setStyleSheet("color:green");
    ui->isRun->setText("游戏运行");
    ui->label_score->setText("0");
    ui->label_speed->setText("20");
    ui->label_food->setText(QString::number(FOODSIZ));
    m_food = new Food(FOODSIZ);
    initMap();
    m_time = new QTimer(this);
    m_time->start(200);  //    30MS *10
    connect(m_time, &QTimer::timeout, this, [ = ]()
    {
        m_snake->MoveSnake();
        update();
        EatFood();
        if (GameOver())
        {
            m_time->stop();
            ui->isRun->setStyleSheet("color:red");
            ui->isRun->setText("结束游戏");
        }
    });
}

SnakeGame::~SnakeGame()
{
    delete ui;
    delete m_pPixmap;
    delete m_pPainter;
    delete m_food;
    delete m_snake;
    delete m_time;
}

//初始化贪吃蛇窗口
void SnakeGame::initMap()
{
    m_pPixmap->fill(QColor(224, 223, 222));   //设置一下纸的颜色
    m_pPainter->begin(m_pPixmap); // 设置画家设备
    QPen pen;
    pen.setColor(QColor(Qt::black));
    pen.setWidth(3);
    m_pPainter->setPen(pen);
//    m_pPainter->drawRect(0, 0, WINDOW_W - 1, WINDOW_H - 1);
    m_pPainter->end();
}

void SnakeGame::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);  // 抗拒齿
    p.drawPixmap(QPoint(0, 0), *m_pPixmap);
    p.save();
    m_food->DrawFood(p);
    p.restore();
    p.save();
    m_snake->DrawSnake(p);
    p.restore();
}

void SnakeGame::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left || event->key() ==  Qt::Key_A)
    {
        if (m_snake->dir != Snake::Right)
        {
            m_snake->dir = Snake::Left;
            isRotate = false;
        }
    }
    else if (event->key() == Qt::Key_Right || event->key() ==  Qt::Key_D)
    {
        if (m_snake->dir != Snake::Left)
        {
            m_snake->dir = Snake::Right;
            isRotate = false;
        }
    }
    else if (event->key() == Qt::Key_Up || event->key() ==  Qt::Key_W)
    {
        if (m_snake->dir != Snake::Down)
        {
            m_snake->dir = Snake::Up;
            isRotate = true;  // 改变了朝向
        }
    }
    else if (event->key() == Qt::Key_Down || event->key() ==  Qt::Key_S)
    {
        if (m_snake->dir != Snake::Up)
        {
            m_snake->dir = Snake::Down;
        }
    }
    else if (event->key() ==  Qt::Key_Space)
    {
        if (m_time->isActive())
        {
            m_time->stop();
        }
        else
        {
            m_time->start(200);
        }
    }
}

void SnakeGame::EatFood()
{
    QPoint snakePos(m_snake->GetSnakeHeadPos().x(), m_snake->GetSnakeHeadPos().y());
    vector<QPoint> foodPosVector = m_food->GetFoodPos();
    vector<QPoint>::iterator it = std::find(foodPosVector.begin(), foodPosVector.end(), snakePos);
    if(it != foodPosVector.end())
    {
        m_snake->lSnake.push_front((m_snake->GetSnakeHeadPos()));
        m_food->updatePos(snakePos);
        score += 10;
        ui->label_score->setText(QString::number(score));
    }
}

bool SnakeGame::GameOver()
{
//    qDebug() << m_snake->GetSnakeHeadPos().x() << m_snake->GetSnakeHeadPos().y();
//    if (!(0 <= m_snake->GetSnakeHeadPos().x() -  2 * SNAKE_W && m_snake->GetSnakeHeadPos().x() + 3 * SNAKE_W <= WINDOW_W ))
//    {
//        return true;
//    }
//    if (!( m_snake->GetSnakeHeadPos().y() + 3 * SNAKE_W <= WINDOW_H) )
//    {
//        return true;
//    }
//    if (isRotate == true && m_snake->GetSnakeHeadPos().y() == 20)
//    {
//        return true;
//    }
    qDebug() << m_snake->GetSnakeHeadPos().x() << m_snake->GetSnakeHeadPos().y();
    if (!(0 <= m_snake->GetSnakeHeadPos().x()  && m_snake->GetSnakeHeadPos().x() <= WINDOW_W
            && 0 <= m_snake->GetSnakeHeadPos().y() && m_snake->GetSnakeHeadPos().y() <= WINDOW_H))
    {
        return true;
    }
    if (!m_snake->bIsSuccess)
    {
        return true;
    }
    return false;
}

