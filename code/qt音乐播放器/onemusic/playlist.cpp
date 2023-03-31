#include "playlist.h"
#include "ui_playlist.h"
#include <QBitmap>
#include <QPainter>

Playlist::Playlist(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Playlist)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    setAttribute(Qt::WA_StyledBackground);   // 设置顶层窗口有效
//    setWindowOpacity(0.);//设置透明度
    // 保持窗口置顶 + 去除边框
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //设置圆角边框
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 30, 30);
    setMask(bmp);
}

Playlist::~Playlist()
{
    delete ui;
}

void Playlist::setSongList(QStringList list)
{
    // 设置listWidget
    ui->listWidget->clear();
    ui->listWidget->addItems(list);
}


