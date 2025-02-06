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
    SearchCombs();
    void setData(Board&, int, QList<Detail>&);
    void restart();

private:
    Board startPrevBoard;
    int startDetailInd;
    QList<Detail> startDetails;
    Board res_board;
    int status;

    bool calc(Board&, int, QList<Detail>&, Board&);

signals:
    void finished(Board);
    void ready();

public slots:
    void run();
    // void terminate();
};

// bool SearchCombs(Board&, int, QList<Detail>&, Board&);

#endif // SEARCHCOMBS_H
