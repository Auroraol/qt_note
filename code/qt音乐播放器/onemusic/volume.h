#ifndef VOLUME_H
#define VOLUME_H

#include <QObject>

class Volume : public QObject
{
    Q_OBJECT
public:
    explicit Volume(QObject* parent = nullptr);
    // 系统音量控制  添加 QT       += axcontainer
#ifdef Q_OS_WIN
    bool setSysVolume(int level);
    int sysVolume();
#endif //Q_OS_WIN

signals:

};

#endif // VOLUME_H
