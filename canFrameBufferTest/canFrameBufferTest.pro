QT += testlib charts

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_canframebuffer.cpp \
    ../app/cansignalbuffer.cpp \
    ../app/chargingtimeestimator.cpp \
    ../app/configuration.cpp \
    canframebuffer_test_data.cpp

HEADERS += \
    ../app/cansignalbuffer.h \
    ../app/chargingtimeestimator.h \
    ../app/configuration.h \
    ../app/movingaverageaccumulator.h

INCLUDEPATH += ../app
