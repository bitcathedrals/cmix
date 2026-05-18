#include <iterator>
#include <algorithm>

#include <cpu/word.h>
#include <cpu/operation.h>
#include <cpu/overflow.h>
#include <parse.h>

void Word::sanitize(void) {
    for(auto i = data_offset; i <= data_max; i++) {
        if (data[i] > positive_max ||
            data[i] < negative_max) {
            throw ArithmeticException("during Word::sanitize",
                                      data[i]);
        }
    }

    // fix the sign
}

Word::Word() : data {sign_default, 0, 0, 0, 0, 0} {}

Word::Word(const Word& other) : data(other.data) {}

Word& Word::operator=(const Word& other) {
    data = other.data;
    return *this;
}

Word& Word::operator=(const parse_t& other) {
    for(auto i = data_offset; i < data_size; i++) {
        data[i] = static_cast<byte>(std::atoi(other[i - data_offset].c_str()));
    }

    sanitize();

    return *this;
}

Word::Word(byte x1, byte x2, byte x3, byte x4, byte x5) {
    data = {sign_default, x1, x2, x3, x4, x5};

    if(x1 < 0) {
        data[sign_field] = sign_negative;
    }
}

Word::Word(Word& other, byte lower, byte upper) {
    data[sign_field] = sign_default;

    lower += data_offset;

    for(byte i = data_min; i <= data_max; i++) {

        if(i >= lower && i <= upper) {
            data[i] = other[i];
        }
        else {
            data[i] = 0;
        }
    }
}

byte& Word::operator[](const byte index) {
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
    }

    return *this;
}

Word& Word::copy_subrange(Word& other, byte lower, byte upper) {
    for(byte i = lower + data_offset; i <= upper; i++) {
        data[i] = other[i];
    }

    return *this;
}

std::ostream& operator<<(std::ostream& output, const Word& x) {
    output << x.data[0] << ":"
           << x.data[1] << ":"
           << x.data[2] << ":"
           << x.data[3] << ":"
           << x.data[4] << ":"
           << x.data[5];

    return output;
};

using input_iterator = std::istreambuf_iterator<char>;

std::istream& operator>>(std::istream& input, Word& x) {
    input_iterator begin(input);
    input_iterator end;

    std::string data(begin, end);

    x = parse_word(data);

    return input;
};
