#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T14:34:43
#
#-------------------------------------------------

QT       -= core gui

TARGET = 3dmath
TEMPLATE = lib

SOURCES += \
    matrix.c \
    quaternion.c \
    queries.c \
    transforms.c

HEADERS += \
    mathlib.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
