#ifndef LYRICFILE_H
#define LYRICFILE_H

#include <QMap>
#include <QObject>

class LyricFile : public QObject
{
    Q_OBJECT
public:
    explicit LyricFile(QObject* parent = nullptr);

    QStringList& getCurrentLyricList();
    QMap<qint64, qint64>& getCurrentLyricMapIndex();
    void getCurrentSongLyric(QString filePath);
signals:

private:
    QStringList m_LyricList;
    QMap<qint64, qint64> m_LyricShow;
    void getCurrentSongLyric(QString filePath, QStringList& LyricList, QMap<qint64, qint64>& LyricShow);

};

#endif // LYRICFILE_H
