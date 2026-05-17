#include <iostream>
#include <map>
#include <string>

#include <cpu/operation.h>

std::ostream& operator<<(std::ostream& output,
                         const UndefinedOperation& undef) {
    output << static_cast<GeneralException>(undef)
           << "undefined operation parameters are: "
           << "i (index) = " << undef.i
           << "x (value) = " << undef.x
           << "v (value) = " << undef.v;

    return output;
};

std::map<OpInfo,std::string> info_to_string = {
    {ADD, "Add Operation"},
};

std::ostream& operator<<(std::ostream& output,
                         const OpException& exception) {
    output << "Operation: "
           << info_to_string[exception.op.info];

    return output;
};
