#include "cpu/cpu.h"

#include "cpu/instruction.h"

Cpu CPU;

Cpu::Cpu(void) {
    reset();
}

void Cpu::reset(void) {
    for(auto i = 0; i < memory_capacity; i++) {
        memory[i].reset();
    }

    A.reset();
    X.reset();

    I1.reset();
    I2.reset();
    I3.reset();
    I4.reset();
    I5.reset();
    I6.reset();

    J.reset();

    overflow = false;

    compare = Cpu::ComparisonIndicator::UNSET;
}

void Cpu::run(int address) {
    static_cast<Instruction*>(&memory[address])->execute();
}
