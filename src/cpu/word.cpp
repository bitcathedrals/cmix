#include <iterator>
#include <algorithm>

#include <sstream>

#include <stdexcept>

#include "cpu/word.h"
#include "cpu/operation.h"
#include "cpu/overflow.h"
#include "parse.h"

void Word::sanitize(void) {
    auto itr_b = data.begin();
    itr_b++; // skip over sign.

    std::for_each(itr_b, data.end(), [](const byte x) {
        if (x > positive_max ||
            x < negative_max) {

            throw ArithmeticException("during Word::sanitize", x);
        }
    });

    // fix the sign
}

Word::Word() : data {sign_default, 0, 0, 0, 0, 0} {}

Word::Word(const Word& other) : data(other.data) {}

Word& Word::operator=(const Word& other) {
    data = other.data;
    return *this;
}

Word& Word::operator=(const std::string& x) {
    parse_t p = parse_word(x);

    if(!(p.size() == data_size)) {
        throw std::out_of_range("word::operator=(const std::string& x) parse is the wrong size");
    }

    auto itr_b = data.begin();
    itr_b++; // skip over the sign

    std::transform(p.begin(), p.end(), itr_b, [](const std::string& x) {
        return static_cast<byte>(std::stoi(x.c_str()));
    });

    sanitize();

    return *this;
}

Word& Word::operator=(const parse_t& p) {
    auto dest_itr_b = data.begin();
    dest_itr_b++;  // skip over sign

    if(!(p.size() == data_size)) {
        std::ostringstream fmt;

        fmt << "word::operator=(const std::parse_t& x) parse is the wrong size: "
            << p.size();

        throw std::out_of_range(fmt.str());
    }

    std::transform(p.begin(), p.end(), dest_itr_b, [](const std::string& x) {
        return static_cast<byte>(std::atoi(x.c_str()));
    });

    sanitize();

    return *this;
}

Word::Word(byte x1, byte x2, byte x3, byte x4, byte x5) {
    data = {sign_default, x1, x2, x3, x4, x5};

    if(x1 < 0) {
        data[sign_field] = sign_negative;
    }

    else {
        data[sign_field] = sign_positive;
    }
}

Word::Word(Word& other, byte lower, byte upper) {
    data[sign_field] = sign_default;

    lower += data_offset;

    for(auto i = lower; i <= data_max; i++) {
        if(i >= lower && i <= upper) {
            data[i] = other[i];
        }
        else {
            data[i] = 0;
        }
    }
}

byte Word::operator[](const byte index) const {
    return data[index];
}

byte Word::operator[](const int index) const {
    return data[index];
}

byte& Word::operator[](const byte index) {
    return data[index];
}

byte& Word::operator[](const int index) {
    return data[index];
}

bool Word::overflowed(byte index) {
    if (data[index] > positive_max ||
        data[index] < negative_max) {
        return true;
    }

    return false;
}

Word& Word::unary(byte low, byte high, OpInfo info, Operation op) {
    for(byte i = low + data_offset; i <= high; i++) {
        data[i] = op(i, data[i]);

        if (overflowed(i)) {
            std::stringstream builder;

            builder << "range from: " << low << "-" << high;

            throw OverflowUnaryException(info,
                                         "Word: Unary Operation",
                                         builder.str(),
                                         i,
                                         data[i]);
        }
    }

    return *this;
}

Word& Word::binary(byte low, byte high, OpInfo info, Operation op, Word v) {
    for(byte i = low + data_offset; i <= high; i++) {
        data[i] = op(i, data[i], v.data[i]);

        if (overflowed(i)) {
            std::stringstream location;

            location << "Word, range from: " << low << "-" << high;

            throw OverflowBinaryException(std::string("word binary operation"),
                                          location.str(),
                                          info,
                                          i,
                                          data[i],
                                          v.data[i]);
        }

    }

    return *this;
}

Word& Word::insert_subrange(Word& other, byte lower, byte upper) {
    upper += 1;

    for(;lower < upper; lower++) {
        data[lower] = other.data[lower];
    }

    return *this;
}

void Word::execute(void) const {
    throw std::logic_error("execute not implemented");
}

std::ostream& operator<<(std::ostream& output, const Word& x) {
    output << static_cast<int>(x.data[0]) << "::"
           << static_cast<int>(x.data[1]) << "::"
           << static_cast<int>(x.data[2]) << "::"
           << static_cast<int>(x.data[3]) << "::"
           << static_cast<int>(x.data[4]) << "::"
           << static_cast<int>(x.data[5]);

    return output;
};

using input_iterator = std::istreambuf_iterator<char>;

std::istream& operator>>(std::istream& input, Word& x) {
    input_iterator begin(input);
    input_iterator end;

    std::string in(begin, end);

    x = parse_word(in);

    return input;
};
