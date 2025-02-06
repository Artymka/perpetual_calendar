#include "searchcombs.h"
#include "randomcounter.h"

SearchCombs::SearchCombs(Board prev_board, int detail_ind, QList<Detail> details)
    : QObject(nullptr),
    start_prev_board(prev_board),
    start_detail_ind(detail_ind),
    start_details(details)
{}

void SearchCombs::run()
{
    calc(start_prev_board, start_detail_ind, start_details, res_board);
    emit finished(res_board);
}

// bool SearchCombs(Board& prev_board, int detail_ind, QList<Detail>& details, Board& res_board)
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
                Board curr_board = prev_board;
                bool success = curr_board.put(x.get(), y.get(), detail, si.get());

                //все детали встали, нужно зарегистрировать календарь
                if (success && detail_ind == 7) {
                    res_board = curr_board;
                    return true;
                }

                if (success) {
                    //отладочное отображение доски
                    //recorder.showBoard(curr_board, 0, 0);

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
