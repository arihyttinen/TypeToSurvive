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

#include "typingview.h"

#include <QFont>
#include <QFontMetrics>
#include <QPaintEvent>
#include <QPainter>

#include <QDebug>


TypingView::TypingView(QWidget *parent) : QLabel(parent)
{
}

void TypingView::appendChar(QChar ch)
{
    Q_ASSERT(!words.isEmpty());
    words.last().text.append(ch);
    update();
}

void TypingView::endWord(bool correct)
{
    Q_ASSERT(!words.isEmpty());
    if (!words.last().text.isEmpty()) {
        words.last().state = correct ? Word::Good : Word::Bad;
        words.append(Word{});
        update();
    }
}

void TypingView::trimWords(int firstIndex) {
    if (firstIndex >= words.size()) {
        words.clear();
    } else {
        while(--firstIndex >= 0) {
            words.removeFirst();
        }

    }
}

void TypingView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setFont(font());
    QFontMetrics metrics(font());

    int index = words.size();
    QRect textRect = rect();
    int hsvSaturation = 255;
    while (index > 0) {
        --index;

        QString word = QStringLiteral("  ") + words[index].text;
        QRect bounds = metrics.boundingRect(textRect, Qt::AlignRight, word);
        QColor color = words[index].stateToQColor(hsvSaturation);
        painter.setPen(color);
        painter.drawText(bounds, word);

        hsvSaturation -= 10;
        textRect.setRight(bounds.left());
        if (textRect.right() < 0 || hsvSaturation <= 0) {
            trimWords(index);
            break;
        }
    }

}
