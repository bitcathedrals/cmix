#include <algorithm>

#include "cpu/cpu.h"

Cpu CPU;

Cpu::Cpu(const Cpu& other)  : A(other.A),
                              X(other.X) {

    std::copy(other.memory.begin(), other.memory.end(), memory.begin());
}

