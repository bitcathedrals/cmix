#include <iostream>
#include <string>

#include <cpu/overflow.h>

std::ostream& operator<<(std::ostream& output,
                         const OverflowOpException exception) {
    output << "overflow: " << info_to_string[exception.op.info]
           << " index = " << exception.index
           << " value = " << exception.value;

    return output;
}

std::ostream& operator<<(std::ostream& output,
                         const OverflowAtException exception) {
    output << "overflow at: " << exception.location
           << exception.ex;
    return output;
}
