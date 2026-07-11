#ifndef CPU_SHORT_H
#define CPU_SHORT_H

#include <iostream>
#include <array>

#include "parse.h"
#include "cpu/defs.h"
#include "cpu/operation.h"

static inline constexpr byte short_word_size = 3;

static inline constexpr byte short_data_bits = 2;

static inline constexpr byte short_positive_max = 64;
static inline constexpr byte short_negative_max = -64;

static inline constexpr byte short_data_size = 2;

static inline constexpr byte short_data_min = 1;
static inline constexpr byte short_data_max = 3;

static inline constexpr byte short_data_offset = 1;

static inline constexpr byte short_sign_field = 0;
static inline constexpr byte short_sign_default = 1;

static inline constexpr byte short_sign_positive = 1;
static inline constexpr byte short_sign_negative = -1;

class Short {
public:
    Short();

    Short(const Short& other);

    Short(Short& other, byte lower, byte upper);

    Short(byte x1, byte x2);

    void reset(void);

    Short& operator=(const Short& right);
    Short& operator=(const parse_t& p);
    Short& operator=(const std::string& x);

    bool operator==(const Short&) const = default;

    byte& operator[](const byte index);

    void sanitize(void);

    bool overflowed(byte index);

    Short& unary(byte low, byte high, OpInfo info, Operation op);
    Short& binary(byte low, byte high, OpInfo info, Operation op, Short v);

    friend std::ostream& operator <<(std::ostream& output, const Short&);
    friend std::istream& operator >>(std::istream& input, Short& x);

private:
    std::array<byte, short_word_size> data;
};

// std::ostream& operator<<(std::ostream& output, const Short& x);
// std::istream& operator>>(std::istream& input, Short& x);

#endif
