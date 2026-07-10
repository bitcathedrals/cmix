#ifndef CPU_H
#define CPU_H

#include <array>

#include "cpu/defs.h"
#include "cpu/word.h"
#include "cpu/short.h"

using memory_index_t = short int;

static inline constexpr memory_index_t memory_capacity = 4000;

class Cpu {
public:
    enum class ComparisonIndicator {
        LESS,
        EQUAL,
        GREATER
    };

    std::array<Word, memory_capacity> memory;

    Word A;
    Word X;

    Short I1;
    Short I2;
    Short I3;
    Short I4;
    Short I5;
    Short I6;

    Short J;

    bool overflow_toggle;

    ComparisonIndicator compare;
};

extern Cpu CPU;

#endif
