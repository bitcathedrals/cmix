#include <iostream>
#include <map>
#include <string>

#include <cpu/operation.h>

std::map<OpInfo,std::string> info_to_string = {
    {LDA, "LDA"},
};

std::ostream& operator<<(std::ostream& output,
                         const OpException exception) {
    output << "Operation: "
           << info_to_string[exception.op.info];

    return output;
};
