#include "cell.h"

Cell::Cell(Cell::ContentType type, int num)
{
    this->type = type;
    this->num = num;
    free = true;
    detailInd = -1;
}

Cell::Cell() : free(false), type(Cell::ContentType::Unavailable), num(0), detailInd(-1) {};
