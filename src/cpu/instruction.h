#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H

#include <string>
#include <utility>
#include <memory>

#include "toolbox.h"
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
    Instruction(void) = default;

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

    void assemble(const std::string assembly);

    virtual void encode(int address,
                        int index,
                        int field_lower,
                        int field_upper);

    void execute(void) const;

    void opcode(void) const;

    virtual ~Instruction() = default;

protected:
    virtual void assemble(std::string::const_iterator& begin,
                          std::string::const_iterator& end);
};

enum class InstructionOpCodes : byte {
    LDA = 8
};

class InstructionFactory : public Singleton<InstructionFactory> {
    friend class Singleton<InstructionFactory>;

public:
    std::shared_ptr<Instruction> insert(const std::string key, Instruction& instruction);
    std::shared_ptr<Instruction> operator[](const std::string key);

private:
    std::map<std::string, std::shared_ptr<Instruction>> table;

    InstructionFactory(void) = default;
};

// extern InstructionTable;

#endif
