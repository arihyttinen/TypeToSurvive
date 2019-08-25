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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QHash>
#include <QVector>

#include "worditem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum { GAME_AREA_WIDTH = 640, GAME_AREA_HEIGHT = 400 };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void on_actionLicense_triggered();

    void on_actionQuit_triggered();

    void on_startButton_clicked();

private:
    struct Word {
        QString word;
        bool correct;
    };

    Ui::MainWindow *ui;

    qreal mCps;

    QTimer mTickTimer;
    QElapsedTimer mWordTimer;
    qint64 mMillisToNextWord = 0.0;

    QHash<QString, WordItem*> mDroppings;

    QVector<QString> mWordList;

    qreal mGroundLevel = 0.9 * GAME_AREA_HEIGHT;

    bool checkWord(const QString &word);
    void tick();
    WordItem *newWordItem(const QString &word);
    void adjustMistakes(int adjustment);
    void adjustMatches(int adjustment);
};

#endif // MAINWINDOW_H
