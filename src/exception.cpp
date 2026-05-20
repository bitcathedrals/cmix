#include <iostream>

#include <exception.h>

std::ostream& operator<<(std::ostream& output,
                         const GeneralException general) {
    output << "Exception! (" << general.context << ")"
           << " time = " << general.timestamp;

    return output;
};

std::ostream& operator<<(std::ostream& output,
                         const ArithmeticException& ex) {
    output << "Arithmetic Overflow! value = "
           << ex.x;

    return output;
};
