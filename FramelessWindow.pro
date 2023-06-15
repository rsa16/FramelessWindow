QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    framelesswindow.cpp \
    main.cpp \
    titlebar.cpp \
    win32utils.cpp

HEADERS += \
    framelesswindow.h \
    titlebar.h \
    win32utils.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsrcs.qrc

DISTFILES += \
    resources/close_icon.svg \
    resources/maximize_icon.svg \
    resources/minimize_icon.svg \
    resources/restore_icon.svg

LIBS += \
    -lDwmapi \
    -lUser32 \
    -lAdvapi32

FORMS += \
    titlebar.ui

