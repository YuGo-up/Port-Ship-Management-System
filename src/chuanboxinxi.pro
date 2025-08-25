QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    main.cpp \
    mainpage.cpp \
    mainpage3.cpp \
    mainpage4.cpp \
    mainwindow.cpp

HEADERS += \
    database.h \
    mainpage.h \
    mainpage3.h \
    mainpage4.h \
    mainwindow.h

FORMS += \
    mainpage.ui \
    mainpage3.ui \
    mainpage4.ui \
    mainwindow.ui

TRANSLATIONS += \
    chuanboxinxi_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc

DISTFILES +=
