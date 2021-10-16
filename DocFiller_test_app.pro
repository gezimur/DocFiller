TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/include \
               $$PWD/src

LIBS += -L$$PWD/lib -L$$PWD/../DuckX/lib/

LIBS += -lDocFiller_lib -lDuckX_lib

SOURCES += \
        $$PWD/src/main.cpp

DESTDIR += $$PWD/bin
TARGET = DocFiller_test_app
