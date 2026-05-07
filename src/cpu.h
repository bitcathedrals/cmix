#ifndef CPU_H_HEADER
#define CPU_H_HEADER

#include <array>

using byte = signed char;

inline constexpr byte data_size = 6;

class operation {
public:
    byte operator()([[maybe_unused]] byte i, [[maybe_unused]] byte x) { return 1; };
    byte operator()([[maybe_unused]] byte i, [[maybe_unused]] byte x, [[maybe_unused]] byte v) { return 1; };
};

class add : operation {
public:
    byte operator()(byte i, byte x, byte v);
};

class word {
public:
    word(byte x1, byte x2, byte x3, byte x4, byte x5);

    word(word &other);

    byte& operator[](byte index);

    byte overflow(byte index);

    word unary(byte low, byte high, operation op);

    word binary(byte low, byte high, operation op, word v);

private:
    std::array<byte, data_size> data;
};

#endif
