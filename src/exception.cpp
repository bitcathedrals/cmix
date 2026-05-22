#include <exception.h>

std::ostringstream& operator<<(std::ostringstream& output,
                               const ThrowableStream& stream) {
    output << "runtime error - context: " << stream.what()
           << " nested: " << stream.str();

    return output;
}

std::ostringstream& operator<<(std::ostringstream& output,
                               const GeneralException& general) {
    output << "Exception - time: " << general.timestamp;

    return output;
};
