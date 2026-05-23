#include <iostream>
#include <map>
#include <string>

#include <cpu/operation.h>

std::map<OpInfo,std::string> OpInfo_to_String = {
    {ADD, "Add Operation"},
};


std::ostringstream& operator<<(std::ostringstream& output,
                               const UndefinedOperation& undef) {

    output << " undefined operation parameters are: "
           << " i value " << static_cast<int>(undef.i)
           << " x value " << static_cast<int>(undef.x)
           << " v value " << static_cast<int>(undef.v);

    return output;
}

std::ostringstream& operator<<(std::ostringstream& output,
                               const ArithmeticException& ex) {
    output << "Arithmetic Exception value = "
           << ex.x;

    return output;
};
