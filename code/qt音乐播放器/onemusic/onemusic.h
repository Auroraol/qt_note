#ifndef ONEMUSIC_H
#define ONEMUSIC_H

#include <QMainWindow>
#include "jsonAnalysis.h"
#include "volume.h"
#include "lyricfile.h"
#include "playlist.h"
#include "musicplayer/musicplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class OneMusic;
}
QT_END_NAMESPACE

class OneMusic : public QMainWindow
{
    Q_OBJECT

public:
    OneMusic(QWidget* parent = nullptr);
    ~OneMusic();

signals:
    void sendSongList(QStringList list);
private slots:
    void slotOnSerach();
    void on_tableWidgetSong_cellDoubleClicked(int row, int column);
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_play_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_playlist_clicked();

    void on_tableWidgetSong_cellClicked(int row, int column);

    void on_pushButton_pre_clicked();

    void on_pushButton_next_clicked();

private:
    Ui::OneMusic* ui;
    const QString API_DOMAIN = "http://iwxyi.com:3000/";
    SongList searchResultSongs;        // typedef QList<Music> SongList;  //搜索的结果
    SongList orderSongs;             // 下载列表

    Music playAfterDownloaded;
    Music playingSong;               // 正在播放歌曲
    Music downloadingSong;           // 正在下载歌曲

    QDir musicFileDir;

    QMediaPlayer* player;            // 播放器
    QMediaPlaylist* playlist;        // 播放列表   //
    QStringList list;                //播放列表信息
    Playlist* playlistWindow;

    bool flag;
    Volume* volume;    // 音量
    LyricFile*  lyric;  // 歌词

    //
    Musicplayer* localSongs;     // 本地歌曲 Musicplayer类


private:
    void creatDirectoryFile();
    void initBtn();
    void initPageSong();
    void signalSlotDefine();
    void setSearchResultTable(SongList songs);
    QString msecondToString(qint64 msecond);
    void downloadSong(Music music);
    QString songPath(const Music& music) const;
    QString lyricPath(const Music& music) const;
    QString coverPath(const Music& music) const;
    void downloadNext();

    void downloadSongCover(Music music);
    void downloadSongLyric(Music music);
    void playLocalSong(Music music);

    void setVolume();
    void showLyric(QString filePath);
    void changeLyricCurrentRow(qint64 position);
    bool eventFilter(QObject* obj, QEvent* event);
    void playList();
};
#endif // ONEMUSIC_H
