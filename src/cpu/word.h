#ifndef CPU_WORD_H
#define CPU_WORD_H

#include <array>

#include "parse.h"
#include "cpu/defs.h"
#include "cpu/operation.h"

//
// word = data + sign
//

inline constexpr byte word_size = 6;

inline constexpr byte data_bits = 6;

inline constexpr byte positive_max = 64;
inline constexpr byte negative_max = -64;

//
// data = word - sign
//

inline constexpr byte data_size = 5;

inline constexpr byte data_min = 1;
inline constexpr byte data_max = 5;

inline constexpr byte data_offset = 1;

//
// sign is a -1 || 1 depending on the sign.
//

inline constexpr byte sign_field = 0;
inline constexpr byte sign_default = 1;

inline constexpr byte sign_positive = 1;
inline constexpr byte sign_negative = -1;

class Word {
public:
    Word();

    explicit Word(const Word& other);

    Word(Word& other, byte lower, byte upper);

    Word(byte x1, byte x2, byte x3, byte x4, byte x5);

    Word& operator=(const Word& right);
    Word& operator=(const parse_t& p);
    Word& operator=(const std::string& x);

    bool operator==(const Word&) const = default;

    byte& operator[](const byte index);
    byte& operator[](const int index);

    void sanitize(void);

    bool overflowed(byte index);

    Word& unary(byte low, byte high, OpInfo info, Operation op);
    Word& binary(byte low, byte high, OpInfo info, Operation op, Word v);

    Word& copy_subrange(Word& other, byte lower, byte upper);

    friend std::ostream& operator <<(std::ostream& output, const Word&);
    friend std::istream& operator >>(std::istream& input, Word& x);

private:
    std::array<byte, word_size> data;
};

std::ostream& operator<<(std::ostream& output, const Word& x);
std::istream& operator>>(std::istream& input, Word& x);

#endif
