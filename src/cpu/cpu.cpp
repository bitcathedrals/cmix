#include "cpu/cpu.h"

#include "cpu/instruction.h"

Cpu CPU;

void Cpu::run(int address) {
    static_cast<Instruction*>(&memory[address])->execute();
}
