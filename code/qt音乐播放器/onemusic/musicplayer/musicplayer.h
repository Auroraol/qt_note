#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include "musicfile/songsfile.h"
#include "lyricfile.h"

class Musicplayer : public QObject
{
    Q_OBJECT
public:
    explicit Musicplayer(QObject* parent = nullptr);

    QMediaPlaylist& getSongsPlayList();
    QStringList& getSongsNameList();
    QMediaPlayer &getCurrentPlayer();
signals:

private:
    Songsfile* m_songsfile;
    LyricFile* m_lyricFile;

    QMediaPlayer m_musicPlayer;
    QMediaPlaylist m_songsPlayList;
    QStringList m_songsNameList;


};

#endif // MUSICPLAYER_H
