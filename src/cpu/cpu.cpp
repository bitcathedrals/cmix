#include <cpu/cpu.h>

Cpu CPU;

Cpu::Cpu(const Cpu& other)  : A(other.A),
                              X(other.X) {
    for(memory_index_t i = 0; i < memory_capacity; i++) {
        memory[i] = other.memory[i];
    }
}

