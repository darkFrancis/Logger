QT       += core

TARGET = Logger
VERSION= 0.1
TEMPLATE = lib
include(../includes/projects.pri)

SOURCES += Logger.cpp
HEADERS += Logger.hpp \
    version.hpp
