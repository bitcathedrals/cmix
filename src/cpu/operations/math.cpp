#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "cpu/operations/ops.h"

byte Add::operator()([[maybe_unused]] byte i, byte x, byte v) {
    return x + v;
}

#endif
