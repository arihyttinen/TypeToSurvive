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

TEMPLATE = lib

TARGET = Box2DLib

QT -= core gui

include(../Options.pri)

INCLUDEPATH += Box2D

SOURCES += $$files("Box2D/Box2D/*.cpp", true)

HEADERS += $$files("Box2D/Box2D/*.h", true)

OTHER_FILES += Box2DLib.pri
