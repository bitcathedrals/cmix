* CMix

CMix is an implementation of the Knuth CMix mythical computer. Mix
is a machine based upon 1960's era technology. It contains a couple
of general purpose registers, 4000 words of memory, and some index
registers.

CMix also has IO in the form of disks, and a punch card interface.

This project aims to implement CMIX with a CLI interface, and related
tools such as an a assembler.

** Goals

- Idiomatic C++, a refresh on idioms and best practices.
- Portable: currently developed on MacOS, Linux, and
  OpenBSD. Buildable with Clang or GCC.
- Correctness and simplicity first. No premature optimization.
- no command dependenies except the compiler and GNU Make.
- Multiple targets for testing, benchmarking, debugging, and prod.
- Minimal external code. External vendor code is checked in as 
  submodules. No patching vendor code in the submodules.
- Exploring compiler features like profile driven optimizations.

Non Goals

- Not competing with other implementations. Other implementations that
  I am aware of are a web version, and a Java version. Both are
  portable in a way, however the web version requires a browser which is
  big and slow, and Java is big and slow.
- Heavy optimization: optimization is a part of the project but
  maximum speed possible is not a goal. For that a machine code translation
  would be a place to start, not an emulator.

* Personal Goals

- to become familiar and proficient in Modern C++. My old C++
  experience is with '03. I am aiming at '17 generally, and '20 for green
  field projects, and '11 for legacy. '03 is too much suffering unless
  I am incentivized heavily.

** History

I wanted to study Knuth's the Art of Computer Programming, and I wanted to
come up to speed with modern C++. This project works on both axis making
the best use of my time possible.

** Process to Progress

*** Phase 1

The first stage is to lay down the core defitions. This would be the 
core abstractions for both instructions and data. I want to make it
an options to load a CSV file into the machine from the CLI or
command line. This will allow IO to be punted.

A lot of the general abstractions or structures would be pulled in as
well in phase 1. Once I had both a Data and Instruction class I should
be able to churn out instructions until done with the CPU, or at least
the most pressing bits.

*** Phase 2

The second phase would be: churning out instructions for both
execution and assembling. Execution involves decoding into MicroCode
the instructions. Assembling involves taking strings and encoding into
instructions.

*** Phase 3

Phase 3 is implementing a external assembler and a linker.

*** Phase 4 is IO.

Implement the disks first, and then the punch card reader.
