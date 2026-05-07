#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <cpu/operations/ops.h>

byte add::operator()([[maybe_unused]] byte i, byte x, byte v) {
    return x + v;
}

#endif
