#ifndef CPU_H
#define CPU_H

#include <array>

#include "cpu/defs.h"
#include "cpu/operation.h"
#include "cpu/word.h"

// move this to short.h later
using memory_index_t = short int;

constexpr memory_index_t memory_capacity = 4000;

class Cpu {
public:
    Cpu() {};

    explicit Cpu(const Cpu& other);

    std::array<Word, memory_capacity> memory;

    Word A;
    Word X;
};

extern Cpu CPU;

#endif
