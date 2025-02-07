#include "searchcombs.h"
#include "randomcounter.h"
#include <QDebug>

SearchCombs::SearchCombs() : QObject(nullptr)
{
    connect(this, &SearchCombs::ready, this, &SearchCombs::run);
    status = 0;
    counter = 0;
};

void SearchCombs::setData(Board& prev_board, int detail_ind, QList<Detail>& details)
{
    startPrevBoard = prev_board;
    startDetailInd = detail_ind;
    startDetails = details;
}

void SearchCombs::restart()
{
    switch (status)
    {
    case 0:
        status = 1;
        emit ready();
        break;
    case 1:
        status = 2;
        break;
    case 2:
        break;
    }
}

void SearchCombs::run()
{
    bool not_terminated = calc(startPrevBoard, startDetailInd, startDetails, res_board);
    if (not_terminated) {
        status = 0;
        emit finished(res_board);
    }
    else {
        status = 1;
        emit ready();
    }
}

bool SearchCombs::calc(Board& prev_board, int detail_ind, QList<Detail>& details, Board& res_board)
{
    //Board board = prev_board;
    // Recorder recorder = Recorder();
    Detail& detail = details[detail_ind];

    //перебор форм
    for (RandomCounter si(detail.shapes.size()); si.valid(); si.up()) {

        //перебор координат
        for (RandomCounter x(7); x.valid(); x.up()) {
            for (RandomCounter y(7); y.valid(); y.up()) {

                // штука, необходимая для остановки перебора
                if (status == 2) {
                    // qDebug() << "mustTerminate in calc";
                    return false;
                }

                Board curr_board = prev_board;
                bool success = curr_board.put(x.get(), y.get(), detail, si.get());

                //все детали встали, нужно зарегистрировать календарь
                if (success && detail_ind == 7) {
                    res_board = curr_board;
                    return true;
                }

                if (success) {
                    counter++;
                    // если положили деталь, с определённой периодичностью показываем доску
                    if (counter % 10000 == 0) {
                        emit intermediate(curr_board);
                    }

                    bool is_filled = calc(curr_board, detail_ind + 1, details, res_board);
                    if (is_filled) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
