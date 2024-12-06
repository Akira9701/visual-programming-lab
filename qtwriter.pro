QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

UI_DIR += ui_headers/

INCLUDEPATH += headers/ ui_headers/


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the fofllowing line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/graphics_editor/antonov.cpp \
    src/graphics_editor/belousov.cpp \
    src/graphics_editor/circle.cpp \
    src/graphics_editor/compositeobject.cpp \
    src/graphics_editor/drawingview.cpp \
    src/graphics_editor/flower.cpp \
    src/graphics_editor/graphics_editor.cpp \
    src/graphics_editor/line.cpp \
    src/graphics_editor/mouse.cpp \
    src/graphics_editor/movableshape.cpp \
    src/graphics_editor/movabletextitem.cpp \
    src/graphics_editor/polygon.cpp \
    src/graphics_editor/rectangle.cpp \
    src/graphics_editor/triangle.cpp \
    src/main.cpp \
    src/main_window/mainwindow.cpp \
    src/text_editor/text_editor.cpp \

HEADERS += \
    headers/antonov.h \
    headers/belousov.h \
    headers/circle.h \
    headers/compositeobject.h \
    headers/drawingview.h \
    headers/flower.h \
    headers/graphics_editor.h \
    headers/line.h \
    headers/mainwindow.h \
    headers/mouse.h \
    headers/movableshape.h \
    headers/movabletextitem.h \
    headers/polygon.h \
    headers/rectangle.h \
    headers/text_editor.h \ \
    headers/triangle.h \
    src/graphics_editor/polygon.h

FORMS += \
    forms/mainwindow.ui \
    forms/text_editor.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
