QT       += core

TARGET = Logger
VERSION= 0.1
TEMPLATE = lib
include(../includes/projects.pri)

SOURCES += src/Logger.cpp
HEADERS += inc/Logger.hpp \
    inc/version/version.hpp

INCLUDEPATH += inc \
    inc/version
