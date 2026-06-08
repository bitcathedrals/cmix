#ifndef CPU_OPERATION_OPS_H
#define CPU_OPERATION_OPS_H

#include "cpu/defs.h"
#include "cpu/operation.h"

class Add : public Operation {
public:
    Add() : Operation(ADD) {}

    byte operator()(byte i, byte x, byte v);
};

#endif
