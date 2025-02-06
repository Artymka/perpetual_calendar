#include "detail.h"
#include <algorithm>

Detail::Detail(const QList<QList<int>>& shape, int ind)
{
    //получение уникальный позиций детали
    QList<QList<int>> curr_shape = shape;
    shapes = QList<QList<QList<int>>>(8);

    for (int i = 0; i < 8; i++) {
        shapes[i] = curr_shape;
        if (i == 3) {
            invert(curr_shape);
        }
        else {
            rotate(curr_shape);
        }
    }

    std::sort(shapes.begin(), shapes.end());
    shapes.erase(std::unique(shapes.begin(), shapes.end()), shapes.end());

    this->ind = ind;
}

void Detail::rotate(QList<QList<int>>& shape)
{
    int n = shape.size(), m = shape[0].size();
    QList<QList<int>> new_shape = QList<QList<int>>(m);

    for (int i = 0; i < m; i++) {
        new_shape[i] = QList<int>(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            new_shape[j][n - i - 1] = shape[i][j];
        }
    }

    shape = new_shape;
}

void Detail::invert(QList<QList<int>>& shape)
{
    int n = shape.size(), m = shape[0].size();
    QList<QList<int>> new_shape = QList<QList<int>>(n);

    for (int i = 0; i < n; i++) {
        new_shape[i] = QList<int>(m);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            new_shape[i][j] = shape[i][m - j - 1];
        }
    }

    shape = new_shape;
}
