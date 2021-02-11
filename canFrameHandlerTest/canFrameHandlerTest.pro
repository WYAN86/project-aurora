QT += testlib serialbus
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_canframehandler.cpp \
    canframehandler_test_data.cpp
SOURCES +=  ../app/canframehandler.cpp

HEADERS +=  ../app/canframehandler.h \
    ../app/canmessages.h

INCLUDEPATH += ../app
