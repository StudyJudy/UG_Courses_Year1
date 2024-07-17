QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    backgroundmusic.qrc \
    backgroundmusicwav.qrc \
    music.qrc

DISTFILES += \
    背景图片/1.jpg \
    背景图片/10.jpg \
    背景图片/2.jpg \
    背景图片/3.jpg \
    背景图片/4.jpg \
    背景图片/5.jpg \
    背景图片/6.jpg \
    背景图片/7.jpg \
    背景图片/8.jpg \
    背景图片/9.jpg \
    背景音乐/John Williams - Hedwig's Theme.mp3 \
    背景音乐/John Williams - Hedwig's Theme.mp3 \
    背景音乐/John Williams - Hedwig's Theme.wav \
    背景音乐/John Williams - Hedwig's Theme.wav
