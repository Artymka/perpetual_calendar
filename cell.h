#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    enum class ContentType {Day, Month, Unavailable};

    bool free;
    Cell::ContentType type;
    int num;
    int detailInd;

    Cell(Cell::ContentType, int);
    Cell();
};

#endif // CELL_H
