# CMix

CMix is an implementation of the Knuth CMix mythical computer. MIX
is a machine based upon 1960's era technology. It contains a couple
of general purpose registers, 4000 words of memory, and some index
registers.

CMix also has IO in the form of disks, and a punch card interface.

This project aims to implement CMIX with a CLI interface, and related
tools such as an a assembler.

## Goals

- Idiomatic C++, a refresh on idioms and C++ Guidelines.
- Portable: currently developed on MacOS, Linux, and
  OpenBSD. Buildable with Clang or GCC.
- Correctness and simplicity first. No premature optimization.
- no command dependenies except the compiler and GNU Make.
- Multiple targets for testing, benchmarking, and prod.
- Minimal external code. External vendor code is checked in as 
  submodules. No patching vendor code in the submodules.
- Exploring compiler features like profile driven optimizations.
- Learn Modern C++
- Have a implementation for reading "The Art of Computer Programming"
- have a nice blend of a CLI for cmix, and the teletype for MIX.
- explore compiler optimization techniques.

## Non Goals

- Not competing with other implementations. Other implementations that
  I am aware of are a web version, and a Java version. Both are
  very heavy.

- Heavy optimization: optimization is a part of the project but
  maximum speed possible is not a goal. For that a machine code translation
  would be a place to start, not an emulator.

## Personal Goals

- to become familiar and proficient in Modern C++. I am targeting '20
  to learn and use.

## Process to Progress

### Phase 1 - Done

The first stage is to lay down the core defitions for both
instructions and data.

A lot of the general abstractions or structures would be pulled in as
well in phase 1. 

Once I had both a Data and Instruction class I should be able to churn
out instructions until done with the CPU, or at least the most
pressing bits.

### Phase 2

I want to make load into memory from a CSV file from the CLI. This
will allow IO to be punted.

The second part involves churning out instructions and creating
a simple one pass assembler. The assembler can be a simplistic
and niave, but any chip these days will run it easily.

two CLI commands: execute and run. Execute will execute a single
instruction. Run will continue execution until a zero word
or end of memory is reached.

### Phase 3

Implement IO such as persistent storage. This will save/load
"machines" or snapshots complete with all IO, memory/register, and
memory contents.

#### Phase 4

Debugger.

### Deps

- googletest - for testing
- libedit - for CLI
