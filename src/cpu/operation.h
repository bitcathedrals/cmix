#ifndef CPU_OPERATION_H
#define CPU_OPERATION_H

#include <cpu/defs.h>

class operation {
public:
    byte operator()([[maybe_unused]] byte i, [[maybe_unused]] byte x) { return 1; };
    byte operator()([[maybe_unused]] byte i, [[maybe_unused]] byte x, [[maybe_unused]] byte v) { return 1; };
};

#endif
