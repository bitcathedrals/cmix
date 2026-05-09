#ifndef CPU_H
#define CPU_H

#include <array>

#include <cpu/defs.h>
#include <cpu/operation.h>

inline constexpr byte data_size = 6;

class word {
public:
    word();

    word(word &other);

    word(byte x1, byte x2, byte x3, byte x4, byte x5);

    word(word &other, byte lower, byte upper);

    byte& operator[](byte index);

    bool overflowed(byte index);

    word& unary(byte low, byte high, operation op);

    word& binary(byte low, byte high, operation op, word v);

    word& copy_subrange(word& other, byte lower, byte upper);

private:
    std::array<byte, data_size> data;
};

inline const short int memory_capacity = 4000;

extern word memory[memory_capacity];

#endif
