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

#include <random>

#include <QString>
#include <QStringList>

#include "utils.h"

static std::random_device random_device;


int Utils::random_in_range(int begin, int end)
{
    auto dist = std::uniform_int_distribution<int>{ begin, end };
    return dist(random_device);
}

void Utils::capitalizeWord(QString &word)
{
    if (word.length() > 0) {
        word[0] = word[0].toUpper();
    }
}

void Utils::capitalizeMultiWord(QChar sep, QString &word)
{
    auto parts = word.split(sep, QString::KeepEmptyParts);
    for (auto &part : parts) {
        capitalizeWord(part);
    }
    word = parts.join(sep);
}
