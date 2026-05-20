#include <iostream>
#include <string>


#include <cpu/overflow.h>

std::ostream& operator<<(std::ostream& output,
                         const OverflowUnaryException& ex) {
    output << "Unary Overflow: " << OpInfo_to_String[ex.op]
           << "@ " << ex.address
           << " index = " << ex.index
           << " value = " << ex.value;

    return output;
}

std::ostream& operator<<(std::ostream& output,
                         const OverflowBinaryException& ex) {
    output << "overflow at: " << ex.address
           << " index" << ex.index
           << " value x = "  << ex.x
           << " value v = " << ex.v;

    return output;
}
