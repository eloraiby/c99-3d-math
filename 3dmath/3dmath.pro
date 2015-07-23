#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T14:34:43
#
#-------------------------------------------------

QT       -= core gui

TARGET = 3dmath
TEMPLATE = lib

QMAKE_CFLAGS	+= -DBUILDING_3DMATH_DLL

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
