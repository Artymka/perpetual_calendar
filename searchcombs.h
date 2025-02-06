#ifndef SEARCHCOMBS_H
#define SEARCHCOMBS_H

#include <QList>
#include <QObject>
#include "board.h"
#include "detail.h"

class SearchCombs : public QObject
{
    Q_OBJECT

public:
    SearchCombs(Board, int, QList<Detail>);

private:
    Board start_prev_board;
    int start_detail_ind;
    QList<Detail> start_details;
    Board res_board;

    bool calc(Board&, int, QList<Detail>&, Board&);

signals:
    void finished(Board);

public slots:
    void run();
};

// bool SearchCombs(Board&, int, QList<Detail>&, Board&);

#endif // SEARCHCOMBS_H
