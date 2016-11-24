QT += core
QT -= gui

CONFIG += c++11

TARGET = SegNet
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
           qimagefinder.cpp \
           cnnsegmentnet.cpp

HEADERS += \
           qimagefinder.h \
           cnnsegmentnet.h

OPENIST_PATH = C:/Programming/OpenIST		   
		   
include( $${OPENIST_PATH}/Sharedfiles/opencv.pri )
include( $${OPENIST_PATH}/Sharedfiles/tinydnn.pri )
include( $${OPENIST_PATH}/Sharedfiles/openmp.pri )
