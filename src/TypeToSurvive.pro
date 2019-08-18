#    Copyright (C) 2019 Ari Hyttinen

#    This file is part of TypeToSurvive program.

#    TypeToSurvive is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    TypeToSurvive is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with TypeToSurvive.  If not, see <https://www.gnu.org/licenses/>.


QT += core gui widgets

TARGET = TypeToSurvive
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++14

QMAKE_CXXFLAGS += -Wall -Wextra

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        typingview.cpp \
        utils.cpp \
        worditem.cpp

HEADERS += \
        mainwindow.h \
        typingview.h \
        utils.h \
        worditem.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc
