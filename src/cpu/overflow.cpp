#include <cpu/overflow.h>
#include <sstream>

void arithmetic_overflow(byte overflowed) {
    std::stringstream ss;
    ss << "cmix byte overflow: " << overflowed;

    throw std::overflow_error(ss.str());
}
