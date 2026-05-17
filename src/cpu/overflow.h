#ifndef CPU_OVERFLOW_H
#define CPU_OVERFLOW_H

#include <stdexcept>

#include <cpu/defs.h>
#include <exception.h>
#include <cpu/operation.h>

class OverflowOpException : public OpException {
public:
    OverflowOpException(const Operation& op,
                        const std::string context,
                        const byte index,
                        const byte value) : OpException(op, context),
                                            index(index),
                                            value(value) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OverflowOpException ex);
    const byte index;
    const byte value;
};

std::ostream& operator<<(std::ostream& output,
                         const OverflowOpException& ex);

class OverflowAtException {
public:
    OverflowAtException(const OverflowOpException& ex,
                        const std::string& location) : ex(ex),
                                                       location(location) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OverflowAtException& ex);

    const OverflowOpException& ex;
    const std::string& location;
};

std::ostream& operator<<(std::ostream& output,
                         const OverflowAtException& exception);

#endif
