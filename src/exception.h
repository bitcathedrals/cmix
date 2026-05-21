#ifndef CPU_EXCEPTION_H
#define CPU_EXCEPTION_H

#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <chrono>
#include <stdexcept>
#include <memory>

using ThrowablePointer = std::unique_ptr<std::ostreamstring>;

class ThrowableStream : public std::runtime_error {
    explicit ThrowableStream(std::string context) : runtime_error(context),
                                                    stream(new ostringstream) {}

    ThrowableStream& operator=(ThrowableStream&& prev) {
        stream = std::move(prev.stream);
        return *this;
    }

    std::string& str(void) { return stream.str(); }

    ThrowablePointer* operator->() {
        return stream;
    }

private:
    ThrowableStream() {}

    ThrowablePointer stream;
}

class GeneralException : public ThrowableStream {
public:
    GeneralException(std::string context) : ThrowableStream(context),
                                            context(context),
                                            timestamp(std::chrono::system_clock::now()) {
    }

    friend std::ostream& operator<<(std::ostream& output,
                                    const GeneralException& general);

    const std::string context;
    const std::chrono::time_point<std::chrono::system_clock> timestamp;
};

std::ostream& operator<<(std::ostream& output,
                         const GeneralException& general);

class ArithmeticException : public std::ThrowableStream {
public:
    ArithmeticException(std::string context, int x) : ThrowableStream(context), x(x) {}

    friend std::ostream& operator<<(std::ostream& output,
                                    const ArithmeticException& ex);
private:
    int x;
};

std::ostream& operator<<(std::ostream& output,
                         const ArithmeticException& general);

#endif
