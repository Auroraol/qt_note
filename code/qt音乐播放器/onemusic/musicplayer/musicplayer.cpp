#include "musicplayer.h"

Musicplayer::Musicplayer(QObject* parent)
    : QObject{parent}
    , m_songsfile(new Songsfile)
    , m_lyricFile(new LyricFile)
{
    m_songsfile->initSongListAndSongNameList(m_songsPlayList, m_songsNameList);
    m_musicPlayer.setMedia(&m_songsPlayList);
}


QMediaPlaylist& Musicplayer::getSongsPlayList(void)  //获取歌曲列表
{
    return m_songsPlayList;
}

QStringList& Musicplayer::getSongsNameList(void)   //获取歌名列表
{
    return m_songsNameList;
}


QMediaPlayer& Musicplayer::getCurrentPlayer(void)  //当前播放器
{
    return m_musicPlayer;
}
