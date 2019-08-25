/*
    Copyright (C) 2019 Ari Hyttinen

    This file is part of TypeToSurvive program.

    TypeToSurvive is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TypeToSurvive is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TypeToSurvive.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef UTILS_H
#define UTILS_H

#include <QChar>

namespace Utils {
int random_in_range(int begin, int end);

void capitalizeWord(QString &word);
void capitalizeMultiWord(QChar sep, QString &word);

static const QChar SEP_SPACE = ' ';
static const QChar SEP_UNDERSCORE = '_';
static const QChar SEP_DASH = '-';
}


#endif // UTILS_H
