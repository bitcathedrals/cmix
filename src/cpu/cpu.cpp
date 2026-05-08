#include <cpu.h>

#include <algorithm>
#include <stdexcept>
#include <sstream>

static const unsigned short int RAM_size = 4000;

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

void arithmatic_overflow(byte overflowed) {
    std::stringstream ss;
    ss << "cmix byte overflow: " << overflowed;

    throw std::overflow_error(ss.str());
}

word::word(byte x1, byte x2, byte x3, byte x4, byte x5) {
    data = {sign_default, x1, x2, x3, x4, x5};

    if(x1 < 0) {
        data[sign_field] = sign_negative;
    }
}

word::word(word &other) : data(other.data) {}

word::word(word &other, byte lower, byte upper) {
    data[sign_field] = sign_default;

    for(byte i = data_min; i <= data_max; i++) {

        if(i >= lower && i <= upper) {
            data[i] = other[i];
        }
        else {
            data[i] = 0;
        }
    }
}

byte& word::operator[](byte index) {
    return data[index + data_offset];
}

bool word::overflowed(byte index) {
    if (data[index + data_offset] > positive_max ||
        data[index + data_offset] < negative_max) {
        return true;
    }

    return false;
}

word& word::unary(byte low, byte high, operation op) {
    for(byte i = low; i <= high; i++) {
        data[i] = op(i, data[i]);

        if (overflowed(i)) {
            arithmatic_overflow(data[i]);
        }
    }

    return *this;
}

word& word::binary(byte low, byte high, operation op, word v) {
    for(byte i = low; i <= high; i++) {
        data[i] = op(i, data[i], v.data[i]);

        if (overflowed(i)) {
            arithmatic_overflow(data[i]);
        }

    }

    return *this;
}

word& word::copy_subrange(word& other, byte lower, byte upper) {
    for(byte i = lower + data_offset; i <= upper; i++) {
        data[i] = other[i];
    }

    return *this;
}
