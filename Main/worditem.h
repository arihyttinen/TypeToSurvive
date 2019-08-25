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

#ifndef WORDITEM_H
#define WORDITEM_H

#include <QGraphicsSimpleTextItem>

class WordItem : public QGraphicsSimpleTextItem
{
public:
    explicit WordItem(const QString &word, const QPointF &velocity, QGraphicsItem *parent = nullptr);

protected:
    void advance(int phase) override;

private:
    QPointF mVelocity;
};


#endif // WORDITEM_H
