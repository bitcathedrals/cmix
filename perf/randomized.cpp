#include "randomized.h"

static std::random_device rd;

Randomized::Randomized(int lower, int upper) : gen(rd()),
                                               distr(lower, upper) {}

int Randomized::next(void) {
    return distr(gen);
}

