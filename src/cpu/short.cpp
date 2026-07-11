#include <iterator>
#include <algorithm>

#include <sstream>

#include "cpu/short.h"
#include "cpu/overflow.h"

void Short::sanitize(void) {
    auto itr_b = data.begin();
    itr_b++; // skip over sign.

    std::for_each(itr_b, data.end(), [](const byte x) {
        if (x > short_positive_max ||
            x < short_negative_max) {

            throw ArithmeticException("during Short::sanitize", x);
        }
    });

    // fix the sign
}

Short::Short() : data {short_sign_default, 0, 0} {}

Short::Short(const Short& other) : data(other.data) {}


void Short::reset() {
    data[0] = short_sign_default;

    for(auto i = short_data_offset; i < short_word_size; i++) {
        data[i] = 0;
    }
}

Short& Short::operator=(const Short& other) {
    data = other.data;
    return *this;
}

Short& Short::operator=(const std::string& x) {
    parse_t p = parse_word(x);

    if(!(p.size() == short_data_size)) {
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

Short& Short::operator=(const parse_t& p) {
    auto dest_itr_b = data.begin();
    dest_itr_b++;  // skip over sign

    if(!(p.size() == short_data_size)) {
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

Short::Short(byte x1, byte x2) {
    data = {short_sign_default, x1, x2};

    if(x1 < 0) {
        data[short_sign_field] = short_sign_negative;
    }

    else {
        data[short_sign_field] = short_sign_positive;
    }
}

Short::Short(Short& other, byte lower, byte upper) {
    data[short_sign_field] = short_sign_default;

    for(byte i = short_data_min; i <= short_data_max; i++) {
        if(i >= lower && i <= upper) {
            data[i] = other[i];
        }
        else {
            data[i] = 0;
        }
    }
}

byte& Short::operator[](const byte index) {
    return data[index];
}

bool Short::overflowed(byte index) {
    if (data[index] > short_positive_max ||
        data[index] < short_negative_max) {
        return true;
    }

    return false;
}

Short& Short::unary(byte low, byte high, OpInfo info, Operation op) {
    for(byte i = low + short_data_offset; i <= high; i++) {
        data[i] = op(i, data[i]);

        if (overflowed(i)) {
            std::stringstream builder;

            builder << "range from: " << low << "-" << high;

            throw OverflowUnaryException(info,
                                         "Short: Unary Operation",
                                         builder.str(),
                                         i,
                                         data[i]);
        }
    }

    return *this;
}

Short& Short::binary(byte low, byte high, OpInfo info, Operation op, Short v) {
    for(byte i = low + short_data_offset; i <= high; i++) {
        data[i] = op(i, data[i], v.data[i]);

        if (overflowed(i)) {
            std::stringstream location;

            location << "Short, range from: " << low << "-" << high;

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

std::ostream& operator<<(std::ostream& output, const Short& x) {
    output << static_cast<int>(x.data[1]) << "-"
           << static_cast<int>(x.data[2]) << "::";

    return output;
};

using input_iterator = std::istreambuf_iterator<char>;

std::istream& operator>>(std::istream& input, Short& x) {
    input_iterator begin(input);
    input_iterator end;

    std::string in(begin, end);

    x = parse_word(in);

    return input;
};
