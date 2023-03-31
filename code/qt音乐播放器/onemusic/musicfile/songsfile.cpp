#include "songsfile.h"
#include <QApplication>


Songsfile::Songsfile(QObject* parent)
    : QObject{parent}
{
    QString m_songFormat = ".mp3";
    QDir m_songDir = QDir(QApplication::applicationDirPath() + "/musics");
    //递归
    m_songsList = m_songDir.entryInfoList(QStringList() << "*.mp3",
                                          QDir::Files, QDir::Name);
}

void Songsfile::initSongListAndSongNameList(QMediaPlaylist& m_songsPlayList,
        QStringList& m_songsNameList)
{
    foreach (QFileInfo fileInfo, m_songsList)
    {
        m_songsNameList.append(fileInfo.fileName().remove(".mp3"));
        QUrl song = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
        if (fileInfo.exists())
        {
            if (fileInfo.suffix().toLower() == QLatin1String("m3u"))  //后缀
            {
                m_songsPlayList.load(song);
            }
            else
            {
                m_songsPlayList.addMedia(song);
            }
        }
        else
        {
            if (song.isValid())
            {
                m_songsPlayList.addMedia(song);
            }
        }
    }
}
