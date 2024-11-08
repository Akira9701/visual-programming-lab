QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


INCLUDEPATH += headers/ ui_headers/


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the fofllowing line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/main_window/mainwindow.cpp \
    src/text_editor/text_editor.cpp \

HEADERS += \
    headers/mainwindow.h \
    headers/text_editor.h \

FORMS += \
    forms/mainwindow.ui \
    forms/text_editor.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


