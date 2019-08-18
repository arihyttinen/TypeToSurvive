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

#ifndef TYPINGVIEW_H
#define TYPINGVIEW_H

#include <QColor>
#include <QLabel>

struct Word {
    enum State { NotReady, Good, Bad };
    QString text = QString();
    State state = NotReady;

    QColor stateToQColor(int saturation) {
        switch (state) {
        case Word::Bad: return QColor::fromHsv(0 /*red*/, saturation, 255);
        case Word::Good: return  QColor::fromHsv(120 /*green*/, saturation, 255);
        default: return Qt::black;
        }
    }
};

class TypingView : public QLabel
{
    Q_OBJECT

public:
    explicit TypingView(QWidget *parent = nullptr);

    QString currentWord() {
        return words.isEmpty() ? QString{} : words.last().text;
    }

signals:

public slots:
    void appendChar(QChar ch);
    void endWord(bool correct);
    void trimWords(int firstIndex);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<Word> words = { Word{} };

};

#endif // TYPINGVIEW_H
