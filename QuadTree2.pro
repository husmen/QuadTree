#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T23:55:55
#
#-------------------------------------------------

QT += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuadTree2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scribblearea.cpp \
    pointquadtree.cpp

HEADERS  += mainwindow.h \
    scribblearea.h \
    pointquadtree.h
