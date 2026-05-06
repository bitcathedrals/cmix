#include "cpu.h"

#include <algorithm>
#include <cassert>

static const unsigned short int RAM_size = 4000;

static const byte data_bits = 6;

static const byte data_mask = 0x3F;
static const byte overflow_mask = 0B1100'0000;

static const byte data_min = 0;
static const byte data_max = 5;

static const byte sign_field = 0;

byte add::operator()([[maybe_unused]] byte i, byte x, byte v) {
    return x + v;
}

word::word(word &other) : data(other.data) {}

byte& word::operator[](byte index) {
    return data[index];
}

byte word::overflow(byte index) {
    byte check = data[index];
    return check & overflow_mask;
}

word word::unary(byte low, byte high, operation op) {
    assert (low >= data_min || high <= data_max);
    assert (low <= high);

    for(byte i = low; i <= high; i++) {
        data[i] = op(i, data[i]);
    }

    return *this;
}

word word::binary(byte low, byte high, operation op, word v) {
    assert (low >= data_min || high <= data_max);
    assert (low <= high);

    for(byte i = low; i <= high; i++) {
        data[i] = op(i, data[i], v.data[i]);
    }

    return *this;
}
