#include "lyricfile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

LyricFile::LyricFile(QObject* parent) : QObject(parent)
{
}

void LyricFile::getCurrentSongLyric(QString filePath, QStringList& LyricList,
                                    QMap<qint64, qint64>& LyricShow)
{
    QString lyricLine;
    QString pos_Lyric;
    QString lyric;
    qint64 lyricTime;
    qint64 index = 0;
    QStringList lyricLinediv;
    QStringList lyricTimediv;
    QFile lyricsFile(filePath);
    if (lyricsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "file of Lyric...";
        QTextStream lineStream(&lyricsFile);
        while (!lineStream.atEnd())
        {
            /*
            [00:00.000] 作词 : 周毅
            [00:01.000] 作曲 : 刘迦宁
            [00:27.520]烽烟起寻爱似浪淘沙
            [00:34.181]遇见她如春水映梨花
            [00:40.947]挥剑断天涯相思轻放下
            [00:47.686]梦中我痴痴牵挂
            */
            lyricLine = lineStream.readLine();
            lyricLinediv = lyricLine.split("]");  //分割每一行
            pos_Lyric = lyricLinediv.at(0).mid(1, 5);  //分割的前半部分取来时间
            lyric = lyricLinediv.at(1);                //后半部分是歌词
            LyricList.append(lyric);
            lyricTimediv = pos_Lyric.split(":");
            lyricTime = (lyricTimediv.at(0).toInt() * 60) + (lyricTimediv.at(1).toInt());  // 时间
            LyricShow.insert(lyricTime, index++);
            lyric.clear();
        }
    }
    lyricsFile.close();
}

void LyricFile::getCurrentSongLyric(QString filePath) //歌词文件
{
    m_LyricList.clear();
    m_LyricShow.clear();
    getCurrentSongLyric(filePath, m_LyricList, m_LyricShow);
}

QStringList& LyricFile::getCurrentLyricList(void) //歌词列表
{
    return m_LyricList;
}

QMap<qint64, qint64>& LyricFile::getCurrentLyricMapIndex(void) //歌词索引
{
    return m_LyricShow;
}
