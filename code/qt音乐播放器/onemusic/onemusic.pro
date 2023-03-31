QT       += core gui  multimedia
QT       += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    lyricfile.cpp \
    main.cpp \
    musicfile/songsfile.cpp \
    musicplayer/musicplayer.cpp \
    onemusic.cpp \
    playlist.cpp \
    volume.cpp

HEADERS += \
    jsonAnalysis.h \
    lyricfile.h \
    musicfile/songsfile.h \
    musicplayer/musicplayer.h \
    onemusic.h \
    playlist.h \
    volume.h

FORMS += \
    onemusic.ui \
    playlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
LIBS += -lwinmm
