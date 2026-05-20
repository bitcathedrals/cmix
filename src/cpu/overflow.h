#ifndef CPU_OVERFLOW_H
#define CPU_OVERFLOW_H

#include <stdexcept>

#include <cpu/defs.h>
#include <exception.h>
#include <cpu/operation.h>

class OverflowUnaryException : std::runtime_error {
public:
    OverflowUnaryException(const Operation& op,
                           const std::string context,
                           const byte index,
                           const byte value) : std::runtime_error(context),
                                               index(index),
                                               value(value) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OverflowOpException ex);
private:
    const byte index;
    const byte value;
};

std::ostream& operator<<(std::ostream& output,
                         const OverflowOpException& ex);

class OverflowBinaryException {
public:
    OverflowAtException(const std::string context&,
                        const std::string& location) : std::runtime_error(context),
                                                       location(location) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OverflowAtException& ex);
    const std::string& location;
};

std::ostream& operator<<(std::ostream& output,
                         const OverflowAtException& exception);

#endif
