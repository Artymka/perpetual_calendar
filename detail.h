#ifndef DETAIL_H
#define DETAIL_H

#include <QList>

class Detail
{
public:
    QList<QList<QList<int>>> shapes;
    int ind;
    Detail(const QList<QList<int>>&, int);

private:
    static void rotate(QList<QList<int>>&);
    static void invert(QList<QList<int>>&);
};

#endif // DETAIL_H
