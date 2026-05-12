#ifndef CPU_OPERATION_H
#define CPU_OPERATION_H

#include <string.h>
#include <map>
#include <iostream>

#include <cpu/defs.h>
#include <cpu/exception.h>

enum OpInfo {
    LDA,
    ADD,
};

extern std::map<OpInfo,std::string> info_to_string;

class Operation {
public:
    const OpInfo info;

    Operation(OpInfo op_info) : info(op_info) {};

    byte operator()([[maybe_unused]] byte i,
                    [[maybe_unused]] byte x) { return 1; };

    byte operator()([[maybe_unused]] byte i,
                    [[maybe_unused]] byte x,
                    [[maybe_unused]] byte v) { return 1; };
};

class OpException : public GeneralException {
public:
    OpException(const Operation& op,
                const std::string context) : GeneralException(context),
                                             op(op) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OpException exception);

    const Operation& op;
};

std::ostream& operator<<(std::ostream& output,
                         const OpException exception);

#endif
