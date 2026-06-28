#ifndef CPU_H
#define CPU_H

#include <array>

#include "cpu/defs.h"
#include "cpu/operation.h"
#include "cpu/word.h"
#include "cpu/short.h"

// move this to short.h later
using memory_index_t = short int;

constexpr memory_index_t memory_capacity = 4000;

class Cpu {
public:
    enum class ComparisonIndicator {
        LESS,
        EQUAL,
        GREATER
    };

    Cpu() {};

    explicit Cpu(const Cpu& other);

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
