#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H

#include <string>
#include <utility>
#include <memory>

#include "cpu/defs.h"
#include "cpu/word.h"

enum class InstructionFields : byte {
    address_begin = 1,
    address_end = 2,
    index = 3,
    field = 4,
    opcode = 5
};

class Instruction : public Word {
public:
    int get_address() const;

    void set_address(int value);
    void set_address(byte upper, byte lower);
    void set_address(std::string value);

    byte get_index() const;

    void set_index(byte v);
    void set_index(std::string value);

    byte get_field() const;
    byte get_field_lower() const;
    byte get_field_upper() const;

    void set_field(byte v);
    void set_field(byte lower, byte upper);
    void set_field(std::string value);

    byte get_opcode() const;

    void set_opcode(byte v);
    void set_opcode(std::string value);

    std::pair<int, std::unique_ptr<Instruction>> assemble(const std::string assembly) const;

    virtual std::unique_ptr<Instruction> assemble(std::string::const_iterator begin,
                                                  std::string::const_iterator end) const;

    void execute(void) const;
    void opcode(void) const;

    virtual ~Instruction() = default;
};

enum class InstructionOpCodes : byte {
    LDA = 8
};

extern std::map<std::string, std::unique_ptr<Instruction>> InstructionFactory;
extern std::map<int, std::unique_ptr<Instruction>> InstructionTable;

#endif
