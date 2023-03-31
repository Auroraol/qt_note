#ifndef SONGSFILE_H
#define SONGSFILE_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfoList>
#include <QDir>

class Songsfile : public QObject
{
    Q_OBJECT
public:
    explicit Songsfile(QObject* parent = nullptr);

    void initSongListAndSongNameList(QMediaPlaylist& m_songsPlayList, QStringList& m_songsNameList);
signals:

private:
    QFileInfoList  m_songsList;

};

#endif // SONGSFILE_H
