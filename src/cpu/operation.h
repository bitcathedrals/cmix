#ifndef CPU_OPERATION_H
#define CPU_OPERATION_H

#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include <stdexcept>

#include <cpu/defs.h>
#include <exception.h>

//
// these are micro ops, not instructions
//

enum OpInfo {
    ADD
};

extern std::map<OpInfo,std::string> OpInfo_to_String;



class UndefinedOperation : public ThrowableStream {
public:
    UndefinedOperation(byte i, byte x, byte v=0) : ThrowableStream("Operation base class reached, undefined operation"),
                                                   i(i), x(x), v(v) {}

    friend std::ostringstream& operator<<(std::ostringstream& output,
                                          const UndefinedOperation& undef);
private:
    byte i;
    byte x;
    byte v;
};

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

class ArithmeticException : public ThrowableStream {
public:
    ArithmeticException(std::string context, int x) : ThrowableStream(context), x(x) {}

    friend std::ostringstream& operator<<(std::ostringstream& output,
                                          const ArithmeticException& ex);
private:
    int x;
};

std::ostream& operator<<(std::ostream& output,
                         const ArithmeticException& general);

#endif
