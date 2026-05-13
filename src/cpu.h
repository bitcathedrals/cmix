#ifndef CPU_H
#define CPU_H

#include <array>

#include <cpu/defs.h>
#include <cpu/operation.h>
#include <cpu/word.h>

inline const short int memory_capacity = 4000;

class Cpu {
public:
    Cpu() {};

    Cpu(const Cpu& other) : A(other.A),
                            X(other.X) {};

    std::array<Word,memory_capacity> memory;

    Word A;
    Word X;
};

extern Cpu CPU;

#endif
