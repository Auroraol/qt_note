#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QListWidget>
#include <QWidget>

namespace Ui
{
    class Playlist;
}

class Playlist : public QWidget
{
    Q_OBJECT

public:
    explicit Playlist(QWidget* parent = nullptr);
    ~Playlist();

public slots:
    void setSongList(QStringList list);
private slots:

private:
    Ui::Playlist* ui;
};

#endif // PLAYLIST_H
