#include <iostream>

#include "exception.h"

std::string ThrowableStream::report(void) const {
    std::string rep(what());

    rep += ":";
    rep += stream.str();

    return rep;
}

std::ostringstream& operator<<(std::ostringstream& output,
                               const ThrowableStream& stream) {
    output << stream.report();
    return output;
}

std::ostringstream& operator<<(std::ostringstream& output,
                               const GeneralException& general) {
    output << "time:" << general.timestamp;
    return output;
};
