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

class Word {
public:
    Word();

    Word(const Word &other);

    Word(byte x1, byte x2, byte x3, byte x4, byte x5);

    Word(Word &other, byte lower, byte upper);

    Word& operator=(const Word& right);

    byte& operator[](const byte index);

    bool overflowed(byte index);

    Word& unary(byte low, byte high, Operation op);

    Word& binary(byte low, byte high, Operation op, Word v);

    Word& copy_subrange(Word& other, byte lower, byte upper);

    friend std::ostream& operator <<(std::ostream& output, const Word&);
    friend std::istream& operator >>(std::istream& input, Word& x);

private:
    std::array<byte, data_size> data;
};

std::ostream& operator<<(std::ostream& output, const Word& x);
std::istream& operator>>(std::istream& input, Word& x);

#endif
