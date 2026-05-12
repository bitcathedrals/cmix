#include <iostream>

#include <cpu/exception.h>

std::ostream& operator<<(std::ostream& output,
                         const GeneralException general) {
    output << "Exception! ("
           << general.context << ")"
           << " time = " << general.timestamp;

    return output;
};
