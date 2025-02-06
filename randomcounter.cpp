#include "randomcounter.h"

RandomCounter::RandomCounter(int length)
{
    srand(time(0));
    limit = length;
    offset = rand() % limit;
    value = 0;
}

void RandomCounter::up()
{
    value++;
}

int RandomCounter::get()
{
    return (offset + value) % limit;
}

bool RandomCounter::valid()
{
    return value < limit;
}
