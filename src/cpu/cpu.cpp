#include <cpu.h>

#include <algorithm>
#include <cassert>

static const unsigned short int RAM_size = 4000;

static const byte data_bits = 6;

static const byte positive_max = 64;
static const byte negative_max = -64;

static const byte data_min = 1;
static const byte data_max = 5;

static const byte sign_field = 0;

word::word(byte x1, byte x2, byte x3, byte x4, byte x5) {
    data = {1, x1, x2, x3, x4, x5};

    if(x1 < 0) {
        data[0] = -1;
    }
}

word::word(word &other) : data(other.data) {}

byte& word::operator[](byte index) {
    return data[index + 1];
}

bool word::overflowed(byte index) {
    if (data[index + 1] > positive_max || data[index + 1] < negative_max) {
        return true;
    }

    return false;
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
