#ifndef CPU_OPERATION_OPS_H
#define CPU_OPERATION_OPS_H

#include <cpu/defs.h>
#include <cpu/operation.h>

class add : public operation {
public:
    byte operator()(byte i, byte x, byte v);
};

#endif
