#ifndef CPU_OVERFLOW_H
#define CPU_OVERFLOW_H

#include <stdexcept>

#include <cpu/defs.h>
#include <exception.h>
#include <cpu/operation.h>

class OverflowUnaryException : std::runtime_error {
public:
    OverflowUnaryException(const OpInfo op,
                           const std::string context,

                           const std::string location,

                           const byte index,
                           const byte value) : std::runtime_error(context),
                                               op(op),

                                               address(location),

                                               index(index),
                                               value(value) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OverflowUnaryException& ex);
private:
    const OpInfo op;
    const std::string& address;

    const byte index;
    const byte value;
};

std::ostream& operator<<(std::ostream& output,
                         const OverflowUnaryException& ex);

class OverflowBinaryException : public std::runtime_error {
public:
    OverflowBinaryException(const std::string& context,
                            const std::string& address,

                            const OpInfo info,

                            const byte index,

                            const byte x,
                            const byte v) : std::runtime_error(context),
                                            address(address),

                                            info(info),

                                            index(index),

                                            x(x),
                                            v(v) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OverflowBinaryException& ex);
private:
    const std::string address;

    const OpInfo info;

    const byte index;

    const byte x;
    const byte v;
};

std::ostream& operator<<(std::ostream& output,
                         const OverflowBinaryException& exception);

#endif
