#include <iostream>
#include <map>
#include <string>

#include <cpu/operation.h>

std::map<OpInfo,std::string> OpInfo_to_String = {
    {ADD, "Add Operation"},
};

std::ostream& operator<<(std::ostream& output,
                         const UndefinedOperation& undef) {
    output << " undefined operation parameters are: "
           << "i (index) = " << undef.i
           << "x (value) = " << undef.x
           << "v (value) = " << undef.v;

    return output;
};

std::ostream& operator<<(std::ostream& output,
                         const ArithmeticException& ex) {
    output << "Arithmetic Exception value = "
           << ex.x;

    return output;
};
