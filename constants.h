#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QList>

const QList<QList<int>> BOARD_PATTERN {
    {-1, -2, -3, -4, -5, -6, 0},
    {-7, -8, -9, -10, -11, -12, 0},
    {1, 2, 3, 4, 5, 6, 7},
    {8, 9, 10, 11, 12, 13, 14},
    {15, 16, 17, 18, 19, 20, 21},
    {22, 23, 24, 25, 26, 27, 28},
    {29, 30, 31, 0, 0, 0, 0}
};

const QList<QList<QList<int>>> DETAILS_SHAPES {
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 1}
    },
    {
        {1, 0, 1},
        {1, 1, 1}
    },
    {
        {1, 1, 1},
        {1, 1, 1}
    },
    {
        {1, 1, 1, 1},
        {0, 0, 1, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 1, 1, 1}
    },
    {
        {1, 0},
        {1, 1},
        {1, 1}
    },
    {
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    },
    {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 1}
    }
};

const QList<QString> DETAILS_COLORS {
    "rgb(222, 47, 47)", // red
    "rgb(39, 199, 36)", // green
    "rgb(93, 47, 222)", // blue
    "rgb(214, 109, 34)", // orange
    "rgb(158, 23, 207)", // purple
    "rgb(214, 195, 26)", // yellow
    "rgb(33, 194, 194)", // cyan
    "rgb(237, 26, 191)" // pink
};

#endif // CONSTANTS_H
