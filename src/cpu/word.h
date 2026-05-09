#ifndef CPU_WORD_H
#define CPU_WORD_H

#include <array>
#include <cpu/defs.h>
#include <cpu/operation.h>

inline constexpr byte data_size = 6;

static const byte data_bits = 6;

static const byte positive_max = 64;
static const byte negative_max = -64;

static const byte data_min = 1;
static const byte data_max = 5;

static const byte data_offset = 1;

static const byte sign_field = 0;
static const byte sign_default = 1;

static const byte sign_positive = 1;
static const byte sign_negative = -1;

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

#endif
