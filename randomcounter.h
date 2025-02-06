#ifndef RANDOMCOUNTER_H
#define RANDOMCOUNTER_H

#include <ctime>
#include <cstdlib>

class RandomCounter
{
public:
    void up();
    int get();
    bool valid();
    RandomCounter(int length);

private:
    int value;
    int limit;
    int offset;
};


#endif // RANDOMCOUNTER_H
