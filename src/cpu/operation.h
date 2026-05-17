#ifndef CPU_OPERATION_H
#define CPU_OPERATION_H

#include <string.h>
#include <map>
#include <iostream>

#include <cpu/defs.h>
#include <exception.h>

//
// these are micro ops, not instructions
//

enum OpInfo {
    ADD
};

class UndefinedOperation : public GeneralException {
public:
    UndefinedOperation(byte i, byte x, byte v=0) : GeneralException("Operation base class reached, undefined operation"),
                                                   i(i), x(x), v(v) {}

    friend std::ostream& operator<<(std::ostream& output,
                                    const UndefinedOperation& undef);
private:
    byte i;
    byte x;
    byte v;
};

std::ostream& operator<<(std::ostream& output,
                         const UndefinedOperation& undef);

extern std::map<OpInfo,std::string> info_to_string;

class Operation {
public:
    const OpInfo info;

    Operation(OpInfo op_info) : info(op_info) {};

    byte operator()(byte i,
                    byte x) { throw UndefinedOperation(i, x); };

    byte operator()(byte i,
                    byte x,
                    byte v) { throw UndefinedOperation(i, x, v); };
};

class OpException : public GeneralException {
public:
    OpException(const Operation& op,
                const std::string context) : GeneralException(context),
                                             op(op) {};

    friend std::ostream& operator<<(std::ostream& output,
                                    const OpException& exception);

    const Operation& op;
};

std::ostream& operator<<(std::ostream& output,
                         const OpException& exception);

#endif
