#-------------------------------------------------
#
# Project created by QtCreator 2017-02-03T20:26:50
#
#-------------------------------------------------

QT       += core gui
QT       += network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../dependencies/decentralised_p2p/build-decentralised_p2p-Desktop_Qt_5_8_0_MSVC2013_64bit-Debug/release/ -ldecentralised_p2p
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../dependencies/decentralised_p2p/build-decentralised_p2p-Desktop_Qt_5_8_0_MSVC2013_64bit-Debug/debug/ -ldecentralised_p2p
else:macx: LIBS += -L$$PWD/../dependencies/decentralised_p2p/build-decentralised_p2p-Desktop_Qt_5_8_0_clang_64bit-Debug  -ldecentralised_p2p
else:unix: LIBS += -L$$PWD/../dependencies/decentralised_p2p/build-decentralised_p2p-Desktop-Debug/ -ldecentralised_p2p

win32: DEFINES += WINDOWS
macx: DEFINES += MACOSX

INCLUDEPATH += $$PWD/../dependencies/decentralised_p2p/src
DEPENDPATH += $$PWD/../dependencies/decentralised_p2p/build-decentralised_p2p-Desktop_Qt_5_8_0_MSVC2013_64bit-Debug/debug

TARGET = decentralised_ui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += static
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    aboutdialog.cpp \
    preferencesdialog.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    aboutdialog.h \
    preferencesdialog.h \
    settings.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    aboutdialog.ui \
    preferencesdialog.ui

RC_FILE = dc.rc

DISTFILES += \
    dc.rc

RESOURCES += \
    resources.qrc

TRANSLATIONS    = decentralised_pt.ts \
                  decentralised_ru.ts \
                  decentralised_de.ts
