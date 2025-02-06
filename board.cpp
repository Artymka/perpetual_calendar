#include "board.h"

Board::Board() {};

Board::Board(const QList<QList<int>>& board_pattern)
{
    // qDebug() << "Board constructor";

    field = QList<QList<Cell>>(board_pattern.size());

    for (int i = 0; i < board_pattern.size(); i++) {
        QList<Cell> row = QList<Cell>(board_pattern[0].size());

        for (int j = 0; j < board_pattern[i].size(); j++) {
            int curr = board_pattern[i][j];
            Cell::ContentType curr_content_type;
            if (curr > 0) {
                curr_content_type = Cell::ContentType::Day;
            }
            else if (curr < 0) {
                curr_content_type = Cell::ContentType::Month;
            }
            else {
                curr_content_type = Cell::ContentType::Unavailable;
            }

            Cell cell = Cell(curr_content_type, abs(curr));
            row[j] = cell;
        }

        field[i] = row;
    }
}

const QList<QString> Board::months {
    " ",
    "Янв",
    "Февр",
    "Март",
    "Апр",
    "Май",
    "Июнь",
    "Июль",
    "Авг",
    "Сент",
    "Окт",
    "Нояб",
    "Дек"
};

QList<QList<QString>> Board::getLabelsPattern(QList<QList<int>> board_pattern)
{
    // qDebug() << "getLabelsPattern";

    QList<QList<QString>> res = QList<QList<QString>>(board_pattern.size());

    for (int i = 0; i < board_pattern.size(); i++) {
        QList<QString> row = QList<QString>(board_pattern[0].size());
        // qDebug() << "Created a row";

        for (int j = 0; j < board_pattern[0].size(); j++) {
            int curr = board_pattern[i][j];
            // qDebug() << "Got curr";
            QString curr_cell;

            if (curr > 0) {
                curr_cell = QString::number(curr);
            }
            else {
                curr_cell = months[abs(curr)];
            }

            // qDebug() << "Got curr_cell: " << curr_cell;

            row[j] = curr_cell;
        }

        res[i] = row;
    }

    return res;
    // qDebug() << "end of getLabelsPattern";
}

bool Board::put(int x, int y, Detail& detail, int si)
{
    //нет свободного места
    if (field.size() - x < detail.shapes[si].size() ||
        field[0].size() - y < detail.shapes[si][0].size()) {
        return false;
    }

    //проверка ячеек
    for (int i = 0; i < detail.shapes[si].size(); i++) {
        for (int j = 0; j < detail.shapes[si][0].size(); j++) {
            //ячейка занята
            if ((!field[x + i][y + j].free ||
                 field[x + i][y + j].type == Cell::ContentType::Unavailable)
                && detail.shapes[si][i][j]) {
                return false;
            }
        }
    }

    //установка детали
    for (int i = 0; i < detail.shapes[si].size(); i++) {
        for (int j = 0; j < detail.shapes[si][0].size(); j++) {

            if (detail.shapes[si][i][j]) {
                field[x + i][y + j].detailInd = detail.ind;
                field[x + i][y + j].free = false;
            }
        }
    }

    return true;
}

void Board::pick(int detail_ind)
{
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            Cell& cell = field[i][j];
            if (cell.detailInd == detail_ind) {
                cell.detailInd = -1;
                cell.free = true;
            }
        }
    }
}

void Board::block(int day, int month)
{
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            Cell &cell = field[i][j];
            if ((cell.type == Cell::ContentType::Day && cell.num == day) ||
                (cell.type == Cell::ContentType::Month && cell.num == month)) {
                cell.free = false;
            }
        }
    }
}
