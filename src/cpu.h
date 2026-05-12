#ifndef CPU_H
#define CPU_H

#include <array>

#include <cpu/defs.h>
#include <cpu/operation.h>
#include <cpu/word.h>

inline const short int memory_capacity = 4000;

extern Word memory[memory_capacity];

//
// registers
//

Word A;
Word X;

#endif
