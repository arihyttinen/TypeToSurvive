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

#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QKeyEvent>
#include <QPointer>
#include <QTextStream>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worditem.h"

#include "utils.h"

#include <QDebug>


/*
 appendFormat_514 parses word data file in particular format

 Example for valid line:
    1    2716396 4,614851 olla (verbi)

 For each line,
 verify that it has 5 items,
 verify that first word is positive number,
 then append 4th word to dest.

 Also modify words based on if they are (erisnimi), and
 split words which have underscores into multiple single words.
*/
template <typename T>
static void appendFormat_514(T &dest, const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        Q_ASSERT(!"Reading resources!");
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    do {
        const QString line = stream.readLine();
        QVector<QStringRef> dataColumns = line.splitRef(Utils::SEP_SPACE, QString::SkipEmptyParts);
        bool ok = false;
        if (dataColumns.count() == 5 && dataColumns[0].toInt(&ok) >= 1 && ok) {
            for(QStringRef wordRef: dataColumns[3].split(Utils::SEP_UNDERSCORE, QString::SkipEmptyParts)) {
                QString word = wordRef.toString();

                if (dataColumns[4] == QStringLiteral("(erisnimi)")) {
                    Utils::capitalizeMultiWord(Utils::SEP_DASH, word);
                }
                dest.append(word);
            }
        }
    } while (!stream.atEnd());
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mCps(2.9)
{
    ui->setupUi(this);

    ui->cpsDisplay->setText(QString::number(mCps, 'f', 1));

    appendFormat_514(mWordList, QStringLiteral(":/data/words-1"));

    // set up the game area
    {
        QGraphicsScene *scene = new QGraphicsScene;
        scene->setBackgroundBrush(Qt::blue);

        scene->setSceneRect(0, 0, GAME_AREA_WIDTH, GAME_AREA_HEIGHT);

        QGraphicsItemGroup *background = new QGraphicsItemGroup;
        scene->addItem(background);

        QGraphicsRectItem *sky = new QGraphicsRectItem;
        sky->setPen(QPen(Qt::blue));
        sky->setBrush(Qt::white);
        sky->setRect(-100 * GAME_AREA_WIDTH, (-100 + 0.02) * GAME_AREA_HEIGHT,
                     300 * GAME_AREA_WIDTH, 100 * GAME_AREA_HEIGHT);
        sky->setGroup(background);

        QGraphicsRectItem *ground = new QGraphicsRectItem;
        ground->setPen(QPen(Qt::darkGreen));
        ground->setBrush(Qt::green);
        ground->setRect(-100 * GAME_AREA_WIDTH, mGroundLevel,
                        300 * GAME_AREA_WIDTH, 100 * GAME_AREA_HEIGHT);
        ground->setGroup(background);

        background->addToGroup(new QGraphicsRectItem());
        ui->gameArea->setScene(scene);
        ui->gameArea->fitInView(ui->gameArea->scene()->sceneRect(), Qt::KeepAspectRatio);
    }

    mTickTimer.setInterval(1000/60); // 60 fps
    mTickTimer.setSingleShot(false);
    QObject::connect(&mTickTimer, &QTimer::timeout, this, &MainWindow::tick);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->text().isEmpty() ||
            (event->modifiers() & ~Qt::ShiftModifier) != 0) {
        // event does not contain text, or has modifiers other than shift
        QMainWindow::keyPressEvent(event);
    }
    else {
        for(auto ch: event->text()) {
            if (ch.isSpace()) {
                bool correct = checkWord(ui->typingView->currentWord());
                ui->typingView->endWord(correct);
            } else if (ch.isPrint()) {
                ui->typingView->appendChar(ch);
            } else if (ch == QChar::fromLatin1(8) || ch == QChar::fromLatin1(127)) {
                // 8 is BS produced by backspace key, 127 is DEL produced by delete key
                adjustMistakes(ui->typingView->deleteWord());
            } else {
                qDebug() << "Ignoring character code" << ch.unicode();
            }
        }
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    ui->gameArea->fitInView(ui->gameArea->scene()->sceneRect(), Qt::KeepAspectRatio);
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ui->gameArea->fitInView(ui->gameArea->scene()->sceneRect(), Qt::KeepAspectRatio);
}

/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

void MainWindow::adjustMistakes(int adjustment){
    ui->mistakesDisplay->display(ui->mistakesDisplay->intValue() + adjustment);
}

void MainWindow::adjustMatches(int adjustment)
{
    ui->matchesDisplay->display(ui->matchesDisplay->intValue() + adjustment);
}

void MainWindow::tick()
{
    ui->gameArea->scene()->advance();

    QList<WordItem*> droppedWords;

    for(auto value: mDroppings) {
        if (value->y() > mGroundLevel) {
            droppedWords.append(value);
        }
    }

    for(auto value: droppedWords) {
        QString word = value->text();
        adjustMistakes(word.length());
        mDroppings.remove(word);
        delete value;
    }

    if(mDroppings.size() <= 0 || mWordTimer.elapsed() > mMillisToNextWord) {
        QString word = mWordList[Utils::random_in_range(0, mWordList.size()-1)];
        mWordTimer.restart();
        mMillisToNextWord = mCps * word.length() * 1000;
        WordItem *item = newWordItem(word);
        ui->gameArea->scene()->addItem(item);
        mDroppings.insertMulti(word, item);
    }
}


bool MainWindow::checkWord(const QString &word)
{
    WordItem* item;
    int matchCount = 0;
    while ((item = mDroppings.take(word)) != nullptr) {
        adjustMatches(word.length());
        delete item;
        ++matchCount;
    }
    if (matchCount == 0) {
        adjustMistakes(word.length());
        return false;
    } else {
        return true;
    }
}


WordItem *MainWindow::newWordItem(const QString &word)
{

    WordItem *item = new WordItem(word);
    item->setFont(QFont("Helvetica", GAME_AREA_WIDTH * 0.04));

    QFontMetrics metrics(item->font());

    int wordWidth = metrics.horizontalAdvance(word);

    item->setX(Utils::random_in_range(0, GAME_AREA_WIDTH - wordWidth));
    return item;
}

void MainWindow::on_actionLicense_triggered()
{
    // TODO: Add GPL license dialog
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_startButton_clicked()
{
    if (mTickTimer.isActive()) {
        mTickTimer.stop();
        ui->startButton->setText("START");
    } else {
        mTickTimer.start();
        ui->startButton->setText("END");
        ui->mistakesDisplay->display(0);
        ui->matchesDisplay->display(0);
        ui->typingView->setFocus();
    }
}
