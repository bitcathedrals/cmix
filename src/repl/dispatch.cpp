#include <iostream>

#include "split.h"
#include "mixer/parser.h"
#include "cpu/cpu.h"
#include "repl/dispatch.h"

const constexpr byte cmd_field = 0;
const constexpr byte read_write_field = 1;

const constexpr byte write_parameter_size = 3;

const constexpr byte write_target_field = 2;
const constexpr byte write_value_field = 2;

std::string status_string(const CmdStatus s) {
    switch(s) {
        case CmdStatus::ok:
            return std::string("Ok");
        case CmdStatus::general_failure:
            return std::string("General Failure");
        case CmdStatus::bad_input:
            return std::string("Bad Input");
        case CmdStatus::bad_value:
            return std::string("Bad Value");
        case CmdStatus::out_of_range:
            return std::string("Out of Range");
    }

    throw std::logic_error("unknown status_string value");
}

static CmdStatus read_op_register(const std::string argument) {
    if(argument == "a") {
        std::cerr << CPU.A << std::endl;
        return CmdStatus::ok;
    }

    if(argument == "x") {
        std::cerr << CPU.X << std::endl;
        return CmdStatus::ok;
    }

    if(argument == "j") {
        std::cerr << CPU.J << std::endl;
        return CmdStatus::ok;
    }

    return CmdStatus::bad_value;
}

static CmdStatus read_index_register(const std::string argument) {
    if(argument == "i1") {
        std::cerr << CPU.I1 << std::endl;
        return CmdStatus::ok;
    }

    if(argument == "i2") {
        std::cerr << CPU.I2 << std::endl;
        return CmdStatus::ok;
    }
    if(argument== "i3") {
        std::cerr << CPU.I3 << std::endl;
        return CmdStatus::ok;
    }

    if(argument == "i4") {
        std::cerr << CPU.I4 << std::endl;
        return CmdStatus::ok;
    }

    if(argument == "i5") {
        std::cerr << CPU.I5 << std::endl;
        return CmdStatus::ok;
    }
    if(argument == "i6") {
        std::cerr << CPU.I6 << std::endl;
        return CmdStatus::ok;
    }

    return CmdStatus::bad_input;
}

static CmdStatus read_memory(const std::string memory_location) {
    Numeric matcher;

    auto begin = memory_location.cbegin();
    auto end = memory_location.cend();

    auto mem = matcher.match(begin, end);

    if (mem.get_type() == Token::label::number && begin == end) {
        int address = std::stoi(mem.get_token());

        if ((address >= 0) && (address < memory_capacity)) {
            std::cerr << CPU.memory[address] << std::endl;
            return CmdStatus::ok;
        }

        std::cerr << "cmix: bad read address: " << memory_location << std::endl;
        return CmdStatus::out_of_range;
    }

    std::cerr << "cmix unknown type (mem): " << memory_location << std::endl;
    return CmdStatus::bad_input;
}

CmdStatus exec_read(const split_t cmd) {
    if(CmdStatus::ok == read_op_register(cmd[read_write_field]) ||
       CmdStatus::ok == read_index_register(cmd[read_write_field]) ||
       CmdStatus::ok == read_memory(cmd[read_write_field])) {
        return CmdStatus::ok;
    }

    std::cerr << "cmix: bad read register/memory argument: " << cmd[read_write_field] << std::endl;
    return CmdStatus::bad_input;
}

static CmdStatus write_op_register(const split_t p) {
    if (p[write_target_field] == "a") {
        CPU.A = split_word(p[write_value_field]);
        std::cerr << "wrote: " << write_target_field << std::endl;

        return  CmdStatus::ok;
    }

    if (p[write_target_field] == "x") {
        CPU.X = split_word(p[write_value_field]);
        std::cerr << "wrote: " << write_target_field << CPU.X << std::endl;

        return  CmdStatus::ok;
    }

    if (p[write_target_field] == "j") {
        CPU.J = split_word(p[write_value_field]);
        std::cerr << "wrote: " << write_target_field << std::endl;

        return  CmdStatus::ok;
    }

    return CmdStatus::bad_input;
}

static CmdStatus write_memory(const split_t p) {
    Numeric matcher;

    auto begin = p[write_target_field].cbegin();
    auto end = p[write_target_field].cend();

    auto memory = matcher.match(begin, end);

    if(memory.get_type() == Token::label::number && begin == end) {
        int address = std::stoi(memory.get_token());

        if ((address >= 0) && (address < memory_capacity)) {
            CPU.memory[address] = split_word(p[write_value_field]);
            return CmdStatus::ok;
        }

        std::cerr << "cmix: bad address: " << p[write_target_field] << std::endl;
        return CmdStatus::out_of_range;
    }

    return CmdStatus::bad_input;
}

static CmdStatus exec_write(const split_t p) {
    size_t size = p.size();

    if (size != write_parameter_size) {
        std::cerr << "bad input - expected " << write_parameter_size
                  << " fields, instead got: "  << p.size() << " fields."  << std::endl;

        return CmdStatus::bad_input;
    }


    if(write_op_register(p) == CmdStatus::ok ||
       write_memory(p) == CmdStatus::ok) {
        return CmdStatus::ok;
    }

    std::cerr << "cmix bad write input (reg/mem): " << p << std::endl;
    return CmdStatus::bad_input;
}

static CmdStatus exec_help() {
    std::cerr << "? help" << std::endl
              << "r <register| address. register = a,,i<1-6>" << std::endl
              << "w <register| address. register = a,x,i<1-6>" << std::endl
              << std::endl;

    return CmdStatus::ok;
}

CmdStatus run_command(const split_t p) {
    size_t size = p.size();

    if(size < 1) {
        std::cerr << "cmix: empty command." << std::endl;
        return CmdStatus::bad_input;
    }

    Command cmd = string_to_command(p[cmd_field]);

    if(cmd == Command::unknown) {
        return CmdStatus::bad_input;
    }

    switch (cmd) {
        case Command::quit:
            std::cerr << "exiting." << std::endl;
            exit(0);

        case Command::read:
            return exec_read(p);
            break;

        case Command::write:
            return exec_write(p);
            break;

        case Command::help:
            return exec_help();
            break;

        case Command::unknown:
            break;
    }

    return CmdStatus::bad_input;
}

