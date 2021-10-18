TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/include \
               $$PWD/src

LIBS += -L$$PWD/lib -L$$PWD/../DuckX/lib/

LIBS += -lDocFiller_lib -lDuckX_lib


#INCLUDEPATH += $$PWD/../DuckX/include \
#               $$PWD/../DuckX/thirdparty \
#               $$PWD/../DuckX/thirdparty/pugixml \
#               $$PWD/../DuckX/thirdparty/zip

#SOURCES += \
#        $$PWD/include/IDocFiller.cpp \
#        $$PWD/src/DocFiller.cpp

#HEADERS += \
#    $$PWD/include/IDocFiller.h \
#    $$PWD/src/DocFiller.h

SOURCES += \
        $$PWD/src/main.cpp

DESTDIR += $$PWD/bin
TARGET = DocFiller_test_app
