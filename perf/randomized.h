#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Randomized {
public:
    Randomized(int lower, int upper);

    int next(void);

private:
    std::mt19937 gen;
    std::uniform_int_distribution<> distr;
};

#endif
