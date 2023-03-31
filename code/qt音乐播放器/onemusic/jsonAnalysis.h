#ifndef JSONANALYSIS_H
#define JSONANALYSIS_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>


struct Album
{
    QString name;
    QString coverUrl;
};

// 音乐信息数据
struct Music
{
    qint64 id;
    QString songName;
    QString artistNames;
    int duration;
    Album album;

    // 解析json
    static Music fromJson(QJsonObject json)  // 静态函数
    {
        Music music;
        music.id = static_cast<qint64>(json.value("id").toDouble());
        music.songName = json.value("name").toString();  // 歌曲名
        // 歌手名称
        QJsonValue ArtistValue = json.value("ar");
        if (ArtistValue.isArray())
        {
            QJsonArray ArtistArray = ArtistValue.toArray();
            QJsonValue ArtistArrayChild = ArtistArray.at(0);
            if (ArtistArrayChild.isObject())
            {
                QJsonObject ArtistObj = ArtistArrayChild.toObject();
                music.artistNames = ArtistObj.value("name").toString();
            }
        }
        QJsonValue albumValue = json.value("al");
        if (albumValue.isObject())
        {
            QJsonObject albumObj = albumValue.toObject();
            // 存储 Album信息
            music.album.name = albumObj.value("name").toString();
            music.album.coverUrl = albumObj.value("picUrl").toString();
        }
        music.duration = json.value("dt").toInt();  // 时长
        return music;
    }

    bool operator==(const Music& music)
    {
        return this->id == music.id;
    }

    // 显示信息
    QString simpleString() const
    {
        return songName + "-" + artistNames;
    }


    bool isValid() const
    {
        return id;
    }

};


typedef QList<Music> SongList;

#endif // JSONANALYSIS_H
