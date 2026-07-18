#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H

#include <string>
#include <utility>
#include <memory>

#include "cpu/defs.h"
#include "cpu/word.h"
#include "mixer/parser.h"

enum class InstructionFields : byte {
    address_begin = 1,
    address_end = 2,
    index = 3,
    field = 4,
    opcode = 5
};

class Instruction : public Word {
public:
    Instruction(void);

    int get_address() const;

    Instruction& set_address(int value);
    Instruction& set_address(byte upper, byte lower);
    Instruction& set_address(std::string value);

    byte get_index() const;

    Instruction& set_index(byte v);
    Instruction& set_index(std::string value);

    byte get_field() const;
    byte get_field_lower() const;
    byte get_field_upper() const;

    Instruction& set_field(byte v);
    Instruction& set_field(byte lower, byte upper);
    Instruction& set_field(std::string value);

    byte get_opcode() const;

    Instruction& set_opcode(byte v);
    Instruction& set_opcode(std::string value);

    std::pair<int, std::unique_ptr<Instruction>> assemble(const std::string assembly) const;

    virtual std::unique_ptr<Instruction> encode(int address,
                                                int index,
                                                int field_lower,
                                                int field_upper) const;
    void execute(void) const;

    void opcode(void) const;

    virtual ~Instruction() = default;

protected:
    void assemble_field(std::string::const_iterator& begin,
                        std::string::const_iterator& end,

                        int& lower,
                        int& upper) const;

    void assemble_address(std::string::const_iterator& begin,
                          std::string::const_iterator& end,

                          int& address,
                          int& index,
                          int& field_lower,
                          int& field_upper) const;

    virtual std::unique_ptr<Instruction> assemble(std::string::const_iterator& begin,
                                                  std::string::const_iterator& end) const;

    std::unique_ptr<Token> address_parser;

    std::unique_ptr<Token> build_address_parser(void);
};

enum class InstructionOpCodes : byte {
    LDA = 8
};

extern std::map<std::string, std::unique_ptr<Instruction>> InstructionFactory;
extern std::map<int, std::unique_ptr<Instruction>> InstructionTable;

#endif
