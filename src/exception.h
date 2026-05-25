#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <stdexcept>

class ThrowableStream : public std::runtime_error {
public:
    ThrowableStream() : runtime_error("no context") {}

    explicit ThrowableStream(std::string context) : runtime_error(context) {}

    std::string report(void) const;

    friend std::ostringstream& operator<<(std::ostringstream& output, const ThrowableStream& stream);

private:
    std::ostringstream stream;
};

std::ostringstream& operator<<(std::ostringstream& output,
                               const ThrowableStream& stream);

class GeneralException : public ThrowableStream {
public:
    GeneralException() {
        ThrowableStream();
    }

    explicit GeneralException(std::string context) : ThrowableStream(context),
                                                     timestamp(std::chrono::system_clock::now()) {}

    friend std::ostringstream& operator<<(std::ostringstream& output,
                                          const GeneralException& general);
private:
    const std::chrono::time_point<std::chrono::system_clock> timestamp;
};

std::ostringstream& operator<<(std::ostringstream& output,
                               const GeneralException& general);

#endif
