#include <iostream>
#include <string>

#include <cpu/overflow.h>

std::ostream& operator<<(std::ostream& output,
                         const OverflowOpException& ex) {
    output << "overflow: " << info_to_string[ex.op.info]
           << " index = " << ex.index
           << " value = " << ex.value;

    return output;
}

std::ostream& operator<<(std::ostream& output,
                         const OverflowAtException& ex) {
    output << "overflow at: " << ex.location;
    return output;
}
