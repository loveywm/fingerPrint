#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T09:21:44
#
#-------------------------------------------------

QT       += core gui

TARGET = FingerPrint
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    src/export.cpp \
    src/file.cpp \
    src/floatfield.cpp \
    src/histogram.cpp \
    src/image.cpp \
    src/imagemanip.cpp \
    src/img_base.cpp \
    src/img_enhance.cpp \
    src/img_morphology.cpp \
    src/import.cpp \
    src/matching.cpp \
    src/minutia.cpp

HEADERS  += widget.h \
    inc/export.h \
    inc/file.h \
    inc/floatfield.h \
    inc/fvs.h \
    inc/fvstypes.h \
    inc/histogram.h \
    inc/image.h \
    inc/imagemanip.h \
    inc/img_base.h \
    inc/import.h \
    inc/matching.h \
    inc/minutia.h

FORMS    += widget.ui


INCLUDEPATH += $$PWD\inc











































