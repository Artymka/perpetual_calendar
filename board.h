#ifndef BOARD_H
#define BOARD_H

#include <QDebug>
#include <QList>
#include <QString>
#include "cell.h"
#include "detail.h"

class Board
{
public:
    QList<QList<Cell>> field;
    bool put(int, int, Detail&, int);
    void pick(int);
    void block(int, int);

    Board(const QList<QList<int>>&);
    Board();

    static QList<QList<QString>> getLabelsPattern(QList<QList<int>>);
    static const QList<QString> months;
};

#endif // BOARD_H
