#-------------------------------------------------
#
# Project created by QtCreator 2012-09-13T13:41:55
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = BasicOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        linearalgebra.cpp mainwindow.cpp \
    basicopenglview.cpp \
    polygon.cpp \
    vertex.cpp

HEADERS  += mainwindow.h linearalgebra.h foundation.h\
    basicopenglview.h \
    fondation.h \
    polygon.h \
    vertex.h

FORMS    += mainwindow.ui
