#include <cpu/cpu.h>
#include <algorithm>

Cpu CPU;

Cpu::Cpu(const Cpu& other)  : A(other.A),
                              X(other.X) {

    std::copy(other.memory.begin(), other.memory.end(), memory.begin());
}

