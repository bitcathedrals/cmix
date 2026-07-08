#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H

#include <string>
#include <array>
#include <stdexcept>

#include "cpu/defs.h"
#include "cpu/word.h"

static inline constexpr byte op_table_length = 64;

enum class InstructionFields : byte {
    address_begin = 0,
    address_end = 1,
    index = 2,
    field = 3,
    opcode = 4
};

enum class InstructionOpCodes : byte {
    LDA = 8
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
    void set_field(byte upper, byte lower);
    void set_field(std::string value);

    byte get_opcode() const;

    void set_opcode(byte v);
    void set_opcode(std::string value);

    virtual void execute(void) const override;

    void opcode_handler(void) const;

    virtual ~Instruction() = default;
};

#endif
