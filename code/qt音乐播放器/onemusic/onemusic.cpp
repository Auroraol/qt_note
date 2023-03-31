#include "onemusic.h"
#include "ui_onemusic.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>			// { }
#include <QJsonArray>			// [ ]
#include <QJsonDocument>	    // 解析json
#include <QJsonDocument>   	    // 解析Json
#include <QJsonParseError>
#include <QJsonValue>			// int float double bool null { } [ ]
#include <QPropertyAnimation>
#include <QTimer>

OneMusic::OneMusic(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::OneMusic)
    , musicFileDir(QApplication::applicationDirPath() + "/musics")
    , player(new QMediaPlayer(this))
    , playlist(new QMediaPlaylist)
    , flag(false)
    , volume(new Volume)
    , lyric(new LyricFile)
    , playlistWindow(new Playlist)
    , localSongs(new Musicplayer)
{
    ui->setupUi(this);
    creatDirectoryFile();
    initBtn();
    initPageSong();
    signalSlotDefine();
    setVolume();
}

OneMusic::~OneMusic()
{
    delete ui;
}

// 创建文件目录
void OneMusic::creatDirectoryFile()
{
    QString strDir = qApp->applicationDirPath() + "/musics";
    QDir dir(strDir);
    if (!dir.exists())
    {
        dir.mkdir(strDir);
    }
}

// 按钮初始化
void OneMusic::initBtn()
{
    ui->pushButton_next->setIcon(QIcon(":/res/icon/next.png"));
    ui->pushButton_pre->setIcon(QIcon(":/res/icon/last.png"));
    ui->pushButton_play->setIcon(QIcon(":/res/icon/pause.png"));
}

// 页面初始化
void OneMusic::initPageSong()
{
    ui->tableWidgetSong->setRowCount(25);
    ui->tableWidgetSong->setColumnCount(4);
    ui->tableWidgetSong->setHorizontalHeaderLabels(QStringList() << "歌曲" << "作者" << "专辑" <<  "时长" );
    ui->tableWidgetSong->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetSong->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidgetSong->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetSong->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetSong->setSelectionMode(QAbstractItemView::SingleSelection);
}

// 信号
void OneMusic::signalSlotDefine()
{
    connect(ui->tbnSearch, &QToolButton::clicked, this, &OneMusic::slotOnSerach);
    //音频播放器状态改变
    connect(player, &QMediaPlayer::mediaStatusChanged, this, [ = ](QMediaPlayer::MediaStatus status)
    {
        if (status == QMediaPlayer::EndOfMedia)
        {
            //EndOfMedia表示没有播放的
            qDebug() << "没有媒体：";
        }
        else if (status == QMediaPlayer::InvalidMedia)
        {
            //InvalidMedia表示加载失败
            qDebug() << "无效媒体：" << playingSong.simpleString();
        }
    });
    // 获得当前音频位置
    static int m_position  = 0;
    connect(player, &QMediaPlayer::positionChanged, this, [ = ](qint64 position)
    {
//        changeLyricCurrentRow(m_position);
//        m_position++;
        changeLyricCurrentRow(position / 1000);
        ui->now_duration->setText(msecondToString(position)); // 显示到标签now_duration上
        // 滑轮跟着改变
        ui->playProgressSlider->setSliderPosition(static_cast<int>(position));
    });
    // 获得音频长度
    connect(player, &QMediaPlayer::durationChanged, this, [ = ](qint64 duration)
    {
        ui->playProgressSlider->setMaximum(duration);  //  设置当前最大值
    });
    // 在滑轮上设置视频播放位置
    connect(ui->playProgressSlider, &QSlider::valueChanged, this, [ = ](int value)
    {
        player->setPosition(value);  // 设置视频播放位置
    });
    ui->playProgressSlider->installEventFilter(this);  //给不同窗口安装事件过滤器
    ui->volumeSlider->installEventFilter(this);
}

// 鼠标点击进行滑动条滑块定位
bool OneMusic::eventFilter(QObject* obj, QEvent* event)
{
    if(obj ==  ui->playProgressSlider)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                int dur =  ui->playProgressSlider->maximum() -  ui->playProgressSlider->minimum();
                int pos =  ui->playProgressSlider->minimum() + dur * ((double)mouseEvent->x() /  ui->playProgressSlider->width());
                if(pos < ( ui->playProgressSlider->sliderPosition()) || pos > ( ui->playProgressSlider->sliderPosition()))
                {
                    ui->playProgressSlider->setValue(pos);
                }
            }
        }
    }
    if(obj ==   ui->volumeSlider)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                int dur =  ui->volumeSlider->maximum() -   ui->volumeSlider->minimum();
                int pos =   ui->volumeSlider->minimum() + dur * ((double)mouseEvent->x() /   ui->volumeSlider->width());
                if(pos < (  ui->volumeSlider->sliderPosition()) || pos > (  ui->volumeSlider->sliderPosition()))
                {
                    ui->volumeSlider->setValue(pos);
                }
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

// TODO
// 音量设置
void OneMusic::setVolume()
{
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(volume->sysVolume());  //volume.h
    connect(ui->volumeSlider, &QSlider::valueChanged, this, [&](int nVal)
    {
        volume->setSysVolume(nVal);  //volume.h
    });
    //监听电脑系统音量变化
    QTimer* pTimerListenVolume = new QTimer(this);
    pTimerListenVolume->start(100);
    connect(pTimerListenVolume, &QTimer::timeout, [ = ]
    {
        int nSysValume = volume->sysVolume();  // 当前系统音量
        if(ui->volumeSlider->value() != nSysValume)
            ui->volumeSlider->setValue(nSysValume);
    });
}


// 搜索
void OneMusic::slotOnSerach()
{
    QString songName = ui->lineEditSearch->text();
    if (songName.trimmed().isEmpty())
    {
        return;
    }
    // url接口
    QString url = "http://iwxyi.com:3000/search?keywords=" + songName.toUtf8().toPercentEncoding();
    // 进行网络下载
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest* request = new QNetworkRequest(url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8"); //在请求中，有一种数据传输的Content-Type 是application/x-www-form-urlencoded。
    request->setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
    connect(manager, &QNetworkAccessManager::finished, this, [ = ](QNetworkReply * reply)
    {
        QString data = reply->readAll();
        // 1. 将字符串解析成QJsonDocument对象
        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &jsonError); //将json解析为UTF-8编码的json文档
        if (!doc.isNull() && jsonError.error != QJsonParseError::NoError)
        {
            //解析出错判断
            qDebug() <<  "Json格式错误！" << jsonError.errorString(); //返回JSON解析错误时报告的错误信息
            return;
        }
        // 2. 获取根对象 { }
        QJsonObject rootObj = doc.object();
        if (rootObj.value("code").toInt() != 200)
        {
            qDebug() << "(返回结果不为200：)";
            return;
        }
        QJsonValue resultValue = rootObj.value("result");
        if (resultValue.isObject())
        {
            // 转换为QJsonObject类型
            QJsonObject resultObj = resultValue.toObject();
            QJsonValue songsValue = resultObj.value("songs");
            if(songsValue.isArray())
            {
                QJsonArray songsArray = songsValue.toArray();  // 得到数组
                searchResultSongs.clear();
                for (auto val : songsArray)
                {
                    // 分析json数据 // 存储songsArray的数据,("歌曲""作者""专辑""时长"之类的)
                    searchResultSongs << Music::fromJson(val.toObject());
                }
            }
        }
        // 设置界面显示
        setSearchResultTable(searchResultSongs);
    });
    manager->get(*request);
}

void OneMusic::setSearchResultTable(SongList songs)
{
    QTableWidget* table = ui->tableWidgetSong;
    // 清空旧数据
    table->clearContents();
    //  设置字符长度
    QFontMetrics fm(font());
    int fw = fm.horizontalAdvance("一二三四五六七八九十十一十二十三十四十五");
    auto createItem = [ = ](QString s)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        if (s.length() > 16 && fm.horizontalAdvance(s) > fw)
        {
            item->setToolTip(s);
            s = s.left(15) + "...";
        }
        item->setText(s);
        return item;
    };
    table->setRowCount(songs.size());
    for (int row = 0; row < songs.size(); row++)
    {
        // 显示
        Music song = songs.at(row);
        table->setItem(row, 0, createItem(song.songName));
        table->setItem(row, 1, createItem(song.artistNames));
        table->setItem(row, 2, createItem(song.album.name));
        table->setItem(row, 3, createItem(msecondToString(song.duration)));
    }
}

QString OneMusic::msecondToString(qint64 msecond)
{
    //arg(msecond / 1000 / 60, 2, 10, QLatin1Char('0')) 一个参数是要填充的数字，第二个参数为最小宽度，第三个参数为进制，第四个参数为当原始数字长度不足最小宽度时用于填充的字符。
    return QString("%1:%2").arg(msecond / 1000 / 60, 2, 10, QLatin1Char('0'))
           .arg(msecond / 1000 % 60, 2, 10, QLatin1Char('0'));
}

// 双击
void OneMusic::on_tableWidgetSong_cellClicked(int row, int column)
{
    if (ui->tableWidgetSong->selectedItems().isEmpty())
    {
        return;
    }
    // 添加音乐
    Music curSong;
    if (row > -1)
    {
        curSong = searchResultSongs.at(row);
    }
    if (!orderSongs.contains(curSong))
    {
        orderSongs.insert(0, curSong);  // 前插
    }
    playList();
    playAfterDownloaded = curSong;
    downloadSong(curSong);  // 下载音乐
//    playLocalSong(curSong);
}

// 单击播放
void OneMusic::on_tableWidgetSong_cellDoubleClicked(int row, int column)
{
    if (ui->tableWidgetSong->selectedItems().isEmpty())
    {
        return;
    }
    // 添加音乐
    Music curSong;
    if (row > -1)
    {
        curSong = searchResultSongs.at(row);
    }
    playLocalSong(curSong);
}

//音乐本地下载
void OneMusic::downloadSong(Music music)
{
    if (QFileInfo(songPath(music)).exists())
    {
        return;
    }
    downloadingSong = music;
    QString url = API_DOMAIN + "song/url?id=" + QString::number(music.id);
    qDebug() << "获取歌曲信息：" << music.simpleString();
    // 下载 歌曲MP3的url数据
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest* request = new QNetworkRequest(url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");
    request->setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.111 Safari/537.36");
    connect(manager, &QNetworkAccessManager::finished, this, [ = ](QNetworkReply * reply)
    {
        QByteArray baData = reply->readAll();
        // 1. 将字符串解析成QJsonDocument对象
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(baData, &error);
        if (error.error != QJsonParseError::NoError)
        {
            qDebug() << error.errorString();
            return;
        }
        // 2. 获取根对象 { }
        QJsonObject rootObj = document.object();
        if (rootObj.value("code").toInt() != 200)
        {
            qDebug() << "返回结果不为200：";
            return;
        }
        QJsonArray dataArray = rootObj.value("data").toArray();
        if (dataArray.size() == 0)
        {
            qDebug() << "未找到歌曲：" << music.simpleString();
            downloadingSong = Music();  // 清空
            downloadNext();
            return;
        }
        QJsonValue dataArrayChild = dataArray.at(0);
        QJsonObject  dataObj = dataArrayChild.toObject();
        QString songUrl = dataObj.value("url").toString();   // 歌曲MP3下载url
        int br = dataObj.value("br").toInt();     // 比率320000
        int size = dataObj.value("size").toInt();  // 3506721
        QString type = dataObj.value("type").toString();   // mp3
        QString encodeType = dataObj.value("encodeType").toString();  // mp3
        qDebug() << " 信息: " << br << size << type << encodeType << songUrl;
        if (size == 0)
        {
            qDebug() << "下载失败， 可能没有版权" << music.simpleString();
            ui->playingNameLabel->setText("没有版权");
            if (playAfterDownloaded == music)
            {
                if (orderSongs.contains(music))
                {
                    orderSongs.removeOne(music);
                    ui->playingNameLabel->clear();  //
                    // 设置信息
                    // 文字长度
                    auto max16 = [ = ](QString s)
                    {
                        if (s.length() > 16)
                        {
                            s = s.left(15) + "...";
                        }
                        return s;
                    };
                    ui->playingNameLabel->setText(max16(music.songName));
                    ui->playingArtistLabel->setText(max16(music.artistNames));
                    //  设置封面
                    if (QFileInfo(coverPath(music)).exists()) // 图片文件存在
                    {
                        // QFileInfo文件信息
                        QPixmap pixmap(coverPath(music));
                        if (pixmap.isNull())
                        {
                            qDebug() << "warning: 本地封面是空的" << music.simpleString() << coverPath(music);
                        }
                        else
                        {
                            ui->playingCoverLablel->setPixmap(pixmap.scaledToHeight(22));    // 封面图像
                        }
                    }
                    else
                    {
                        // 下载图片封面
                        downloadSongCover(music);
                    }
                    player->stop();
                }
            }
            downloadingSong = Music();
            downloadNext();
            return;
        }
        // 下载歌曲本身
        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply* reply1 = manager.get(QNetworkRequest(QUrl(songUrl)));
        // 请求结束并完成下载后退出子事件循环
        connect(reply1, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        // 开启子事件循环
        loop.exec();
        QByteArray baData1 = reply1->readAll();
        QString strPath = songPath(music);   //歌曲保存路径
        QFile file(strPath);
        file.open(QIODevice::WriteOnly);
        file.write(baData1);  // 下载
        file.flush();
        file.close();
        if (playAfterDownloaded == music)
        {
            playLocalSong(music);
        }
        downloadingSong = Music();  // 置空
        downloadNext();  //下载下一个歌曲
    });
    manager->get(*request);
    downloadSongLyric(music);      // 下载歌词
    downloadSongCover(music);      // 下载封面
}

void OneMusic::downloadSongLyric(Music music)
{
    if (QFileInfo(lyricPath(music)).exists())
    {
        return;
    }
    downloadingSong = music;
    QString url = API_DOMAIN + "lyric?id=" + QString::number(music.id);
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest* request = new QNetworkRequest(url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");
    request->setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.111 Safari/537.36");
    connect(manager, &QNetworkAccessManager::finished, this, [ = ](QNetworkReply * reply)
    {
        QByteArray baData = reply->readAll();
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(baData, &error);
        if (error.error != QJsonParseError::NoError)
        {
            qDebug() << error.errorString();
            return;
        }
        QJsonObject json = document.object();
        if (json.value("code").toInt() != 200)
        {
            qDebug() << ("返回结果不为200");
            return;
        }
        QString lrc = json.value("lrc").toObject().value("lyric").toString();
        // 下载歌曲
        if (!lrc.isEmpty())
        {
            QFile file(lyricPath(music));
            file.open(QIODevice::WriteOnly);
            QTextStream stream(&file);
            stream << lrc;
            file.flush();
            file.close();
            qDebug() << "下载歌曲完成: " << music.simpleString();
        }
        else
        {
            qDebug() << "warning: 下载的歌词是空的" << music.simpleString();
        }
    });
    manager->get(*request);
}

void OneMusic::downloadSongCover(Music music)
{
    if (QFileInfo(coverPath(music)).exists())
    {
        return;
    }
    downloadingSong = music;
    QString url = API_DOMAIN + "song/detail?ids=" + QString::number(music.id);
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest* request = new QNetworkRequest(url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");
    request->setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.111 Safari/537.36");
    connect(manager, &QNetworkAccessManager::finished, this, [ = ](QNetworkReply * reply)
    {
        QByteArray baData = reply->readAll();
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(baData, &error);
        if (error.error != QJsonParseError::NoError)
        {
            qDebug() << error.errorString();
            return;
        }
        QJsonObject json = document.object();
        if (json.value("code").toInt() != 200)
        {
            qDebug() << "返回结果不为200";
            return;
        }
        QJsonArray array = json.value("songs").toArray();
        if (array.size() == 0)
        {
            qDebug() << "未找到歌曲封面: " << music.simpleString();
            downloadingSong = Music();
            downloadNext();
            return;
        }
        json = array.first().toObject();
        QString url = json.value("al").toObject().value("picUrl").toString();
        qDebug() << "封面地址: " << url;
        // 开始下载封面
        static QNetworkAccessManager manager;
        static QEventLoop loop;
        QNetworkReply* reply1 = manager.get(QNetworkRequest(QUrl(url)));
        //请求结束并下载完成后，退出子事件循环
        connect(reply1, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        //开启子事件循环
        loop.exec();
        QByteArray baData1 = reply1->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(baData1);
        ui->playingCoverLablel->setPixmap(pixmap);
        if (!pixmap.isNull())
        {
            QFile file(coverPath(music));
            file.open(QIODevice::WriteOnly);
            file.write(baData1);
            file.flush();
            file.close();
//            // 正是当前要播放的歌曲
            if (playAfterDownloaded == music || playingSong == music)
            {
                pixmap = pixmap.scaledToHeight(22);
                ui->playingCoverLablel->setPixmap(pixmap);
            }
        }
        else
        {
            qDebug() << "warning: 下载的封面是空的" << music.simpleString();
        }
    });
    manager->get(*request);
}

// 歌曲保存路径
QString OneMusic::songPath(const Music& music) const
{
    return musicFileDir.absoluteFilePath(QString::number(music.id) + ".mp3");
}

// 歌曲封面保存路径
QString OneMusic::coverPath(const Music& music) const
{
    return musicFileDir.absoluteFilePath(QString::number(music.id) + ".jpg");
}

// 歌词保存路径
QString OneMusic::lyricPath(const Music& music) const
{
    return musicFileDir.absoluteFilePath(QString::number(music.id) + ".lrc");
}

// 下载下一个
void OneMusic::downloadNext()
{
    // 正在下载的歌已经下载了/即将下载的队列是空的
    if (downloadingSong.isValid() || !orderSongs.size())
    {
        return;
    }
    Music music = orderSongs.takeFirst();   // 删除并得到链表第一个数据
    if (!music.isValid())
    {
        return downloadNext();
    }
    downloadSong(music);
}

// 播放音乐
void OneMusic::playLocalSong(Music music)
{
    qDebug() << "开始播放" << music.simpleString();
    if (!QFileInfo(songPath(music)).exists())
    {
        qDebug() << "error:未下载歌曲：" << music.simpleString() << "开始下载";
        playAfterDownloaded = music;
        downloadSong(music);
    }
    // 设置信息
    auto max16 = [ = ](QString s)
    {
        if (s.length() > 16)
        {
            s = s.left(15) + "...";
        }
        return s;
    };
    ui->pushButton_play->setIcon(QIcon(":/res/icon/play.png"));
    ui->playingNameLabel->setText(max16(music.songName));
    ui->playingArtistLabel->setText(max16(music.artistNames));
    ui->all_duration->setText(msecondToString(music.duration));
    // 设置封面
    if (QFileInfo(coverPath(music)).exists())
    {
        QPixmap pixmap(coverPath(music), "1");
        if (pixmap.isNull())
        {
            qDebug() << "warning: 本地封面是空的" << music.simpleString() << coverPath(music);
        }
        // 自适应高度
        pixmap = pixmap.scaledToHeight(22);
        ui->playingCoverLablel->setPixmap(pixmap);
    }
    else
    {
        downloadSongCover(music);
    }
    // 设置歌词
    if (QFileInfo(lyricPath(music)).exists())
    {
        showLyric(lyricPath(music));
    }
    else
    {
        downloadSongLyric(music);
    }
    // 开始播放
    playingSong = music;
    player->setMedia(QUrl::fromLocalFile(songPath(music)));
    player->setPosition(0);
    player->play();
    //emit signalSongPlayStarted(music);
    setWindowTitle(music.songName);
    // 添加到本地歌曲
//    if (localSongs.contains(music))
//    {
//        qDebug() << "本地歌曲已存在：" << music.simpleString();
//        return;
//    }
//    else
//    {
//        localSongs.append(music);
//    }
}

void OneMusic::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void OneMusic::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// 显示歌词
void OneMusic::showLyric(QString filePath)
{
    lyric->getCurrentSongLyric(filePath);
    // 设置listWidget
    ui->lyricList->clear();
    ui->lyricList->addItems(lyric->getCurrentLyricList());
    for (int i = 0; i < lyric->getCurrentLyricList().size(); i++)
    {
        ui->lyricList->item(i)->setTextAlignment(Qt::AlignHCenter);  //居中
        ui->lyricList->item(i)->setForeground(Qt::blue);  //字体颜色
        //需要关闭掉鼠标移动到条目上方时改变颜色，
        ui->lyricList->item(i)->setFlags(Qt::NoItemFlags);
        ui->lyricList->item(i)->setFlags(Qt::ItemIsEnabled);
    }
}

//当前行的字体改变
void OneMusic::changeLyricCurrentRow(qint64 position)
{
    if (lyric->getCurrentLyricMapIndex().contains(position))
    {
        int m_currentRow =  lyric->getCurrentLyricMapIndex().value(position);  //当前行索引
        int m_maxRows =  lyric->getCurrentLyricMapIndex().value(lyric->getCurrentLyricMapIndex().keys().last()); //歌词最大行索引
        ui->lyricList->setCurrentRow(m_currentRow);
        ui->lyricList->item(m_currentRow)->setForeground(Qt::green);
        ui->lyricList->item(m_currentRow)->setFont(QFont("current_font", 13, QFont::DemiBold));  //设置当前行的字体
        //恢复其他行的字体
        if (m_currentRow > 0)
        {
            for (int i = 0; i < m_currentRow; i++)
            {
                ui->lyricList->item(i)->setForeground(Qt::blue);
                ui->lyricList->item(i)->setFont(QFont());
            }
            for (int i = m_currentRow + 1; i <= m_maxRows; i++)
            {
                ui->lyricList->item(i)->setForeground(Qt::blue);
                ui->lyricList->item(i)->setFont(QFont());
            }
        }
    }
}


// 下载列表初始话
void OneMusic::playList()
{
    list.clear();
    for (int i = 0; i < orderSongs.size(); i++)
    {
        list.append( orderSongs.at(i).songName + "-" + orderSongs.at(i).artistNames);
    }
    emit sendSongList(list);
    connect(this, &OneMusic::sendSongList, playlistWindow, &Playlist::setSongList);
}

void OneMusic::on_pushButton_playlist_clicked()
{
    if (playlistWindow->isHidden())
    {
        playlistWindow->show();
    }
    else
    {
        playlistWindow->hide();
    }
}

// TODO

// 模式修改
void OneMusic::on_comboBox_currentIndexChanged(int index)
{
    /*
    // 设置模式
    enum
    {
        SEQUENTIAL,  // 0
        RANDOM,
        LOOP,
        ONCE,
        ONELOOP
    };
    switch (index)
    {
            qDebug() << "修改模式";
        case ONCE:
            localSongs->getSongsPlayList().setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            break;
        case ONELOOP:
            localSongs->getSongsPlayList().setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            break;
        case SEQUENTIAL:
            localSongs->getSongsPlayList().setPlaybackMode(QMediaPlaylist::Sequential);
            break;
        case LOOP:
            localSongs->getSongsPlayList().setPlaybackMode(QMediaPlaylist::Loop);
            break;
        case RANDOM:
            localSongs->getSongsPlayList().setPlaybackMode(QMediaPlaylist::Random);
            break;
        default:
            break;
    }
    */
}

//**************播放和暂停*****************
void OneMusic::on_pushButton_play_clicked()
{
    flag = !flag;
    if (flag)
    {
        ui->pushButton_play->setIcon(QIcon(":/res/icon/pause.png"));
        player->pause();
        //localSongs->getCurrentPlayer().pause();
    }
    else
    {
        ui->pushButton_play->setIcon(QIcon(":/res/icon/play.png"));
        player->play();
        //localSongs->getCurrentPlayer().play();
    }
}


static int index = 0;
//********************上一曲*********************
void OneMusic::on_pushButton_pre_clicked()
{
//    if (localSongs->getSongsPlayList().currentIndex() <= 0)
//    {
//        localSongs->getSongsPlayList().setPlaybackMode(QMediaPlaylist::Loop);  //播放列表循环模式
//    }
//    localSongs->getSongsPlayList().setCurrentIndex(localSongs->getSongsPlayList().previousIndex());
//    localSongs->getCurrentPlayer().play();
    index--;
    if (index < 0 )
    {
        index = 0;
    }
    playLocalSong(orderSongs.at(index));
}


//********************下一曲*********************
void OneMusic::on_pushButton_next_clicked()
{
//    localSongs->getSongsPlayList().setPlaybackMode(QMediaPlaylist::Loop);
//    localSongs->getSongsPlayList().setCurrentIndex(localSongs->getSongsPlayList().nextIndex());
//    localSongs->getCurrentPlayer().play();
    index++;
    if (index > orderSongs.size() - 1)
    {
        index = orderSongs.size() - 1;
    }
    playLocalSong(orderSongs.at(index));
}



