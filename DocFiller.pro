TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../DuckX/include \
               $$PWD/../DuckX/thirdparty \
               $$PWD/../DuckX/thirdparty/pugixml \
               $$PWD/../DuckX/thirdparty/zip

LIBS += -L$$PWD/../DuckX/lib/

LIBS += -lDuckX_lib

SOURCES += \
        $$PWD/src/main.cpp

DESTDIR += $$PWD/bin
TARGET = DocFiller
