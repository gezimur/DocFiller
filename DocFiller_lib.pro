TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../DuckX/include \
               $$PWD/../DuckX/thirdparty \
               $$PWD/../DuckX/thirdparty/pugixml \
               $$PWD/../DuckX/thirdparty/zip \
               $$PWD/include \
               $$PWD/src

LIBS += -L$$PWD/../DuckX/lib/

LIBS += -lDuckX_lib

SOURCES += \
        $$PWD/include/IDocFiller.cpp \
        $$PWD/src/DocFiller.cpp

HEADERS += \
    $$PWD/include/IDocFiller.h \
    $$PWD/src/DocFiller.h

DESTDIR += $$PWD/lib
TARGET = DocFiller_lib
