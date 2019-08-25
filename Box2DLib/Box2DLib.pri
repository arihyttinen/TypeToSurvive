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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Box2DLib/release/ -lBox2DLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Box2DLib/debug/ -lBox2DLib
else:unix: LIBS += -L$$OUT_PWD/../Box2DLib/ -Box2DLib

INCLUDEPATH += $$PWD/../Box2dLib/Box2D

DEPENDPATH += $$PWD/../Box2dLib/Box2D
