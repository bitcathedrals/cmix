#include <cpu/word.h>
#include <cpu/operation.h>
#include <cpu/overflow.h>

Word::Word() : data {sign_field, 0, 0, 0, 0, 0} {}

Word::Word(Word &other) : data(other.data) {}

Word::Word(byte x1, byte x2, byte x3, byte x4, byte x5) {
    data = {sign_default, x1, x2, x3, x4, x5};

    if(x1 < 0) {
        data[sign_field] = sign_negative;
    }
}

Word::Word(Word &other, byte lower, byte upper) {
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

byte& Word::operator[](byte index) {
    return data[index + data_offset];
}

bool Word::overflowed(byte index) {
    if (data[index + data_offset] > positive_max ||
        data[index + data_offset] < negative_max) {
        return true;
    }

    return false;
}

Word& Word::unary(byte low, byte high, Operation op) {
    for(byte i = low; i <= high; i++) {
        data[i] = op(i, data[i]);

        if (overflowed(i)) {
            throw OverflowOpException(op, "unary operation", i, data[i]);
        }
    }

    return *this;
}

Word& Word::binary(byte low, byte high, Operation op, Word v) {
    for(byte i = low; i <= high; i++) {
        data[i] = op(i, data[i], v.data[i]);

        if (overflowed(i)) {
            throw OverflowOpException(op, "binary operation", i, data[i]);
        }

        if (v.overflowed(i)) {
            throw OverflowOpException(op, "binary operation", i, data[i]);
        }
    }

    return *this;
}

Word& Word::copy_subrange(Word& other, byte lower, byte upper) {
    for(byte i = lower + data_offset; i <= upper; i++) {
        data[i] = other[i];
    }

    return *this;
}
