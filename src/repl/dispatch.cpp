#include <iostream>

#include "parse.h"
#include "cpu/cpu.h"
#include "repl/dispatch.h"

const constexpr byte cmd_field = 0;
const constexpr byte type_field = 1;
const constexpr byte adr_field = 2;

const constexpr byte data_field = 3;

const constexpr byte read_parse_size = 3;
const constexpr byte write_parse_size = 4;

static CmdStatus exec_read(const parse_t p);
static CmdStatus exec_write(const parse_t p);

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

    return std::string("unknown CmdStatus in cmd_status_string");
}

std::string cmd_string(const parse_t p) {
    return p[cmd_field];
}

CmdStatus run_command(const parse_t p) {
    char size = p.size();

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

    case Command::unknown:
        break;
    }

    return CmdStatus::bad_input;
}

static CmdStatus exec_read(const parse_t p) {
    int size = p.size();

    if (size != read_parse_size) {
        std::cerr << "cmix bad input, expected " << size << p << std::endl;
        return CmdStatus::bad_input;
    }

    if (p[type_field] == "reg") {
        if (p[adr_field] == "A") {
            std::cerr << CPU.A << std::endl;
        }

        if (p[adr_field] == "X") {
            std::cerr << CPU.X << std::endl;
        }

        return CmdStatus::ok;
    }

    if (p[type_field] == "mem") {
        int address = std::atoi(p[adr_field].c_str());

        if ((address >= 0) && (address < memory_capacity)) {
            std::cerr << CPU.memory[address] << std::endl;
        }
        else {
            std::cerr << "cmix: bad address: " << p[adr_field] << std::endl;
            return CmdStatus::out_of_range;
        }

        return CmdStatus::ok;
    }

    std::cerr << "cmix unknown type (reg/mem): " << p[type_field] << std::endl;
    return CmdStatus::bad_input;
}

static CmdStatus exec_write(const parse_t p) {
    byte size = p.size();

    if (size != write_parse_size) {
        std::cerr << "bad input - expected " << write_parse_size
                  << " fields, instead: "  << p.size() << std::endl;

        return CmdStatus::bad_input;
    }

    if (p[type_field] == "reg") {
        if (p[adr_field] == "A") {
            CPU.A = p[data_field];
            std::cerr << CPU.A << std::endl;
        }

        if (p[adr_field] == "X") {
            CPU.X = p[data_field];
            std::cerr << CPU.X << std::endl;
        }

        return CmdStatus::ok;
    }

    if (p[type_field] == "mem") {
        int address = std::atoi(p[adr_field].c_str());

        if ((address >= 0) && (address < memory_capacity)) {
           CPU.memory[address] = p[data_field];

            std::cerr << CPU.memory[address] << std::endl;

            return CmdStatus::ok;
        }
        else {
            std::cerr << "cmix: bad address: " << p[adr_field] << std::endl;
            return CmdStatus::out_of_range;
        }
    }

    std::cerr << "cmix unknown type (reg/mem): " << p[type_field] << std::endl;
    return CmdStatus::bad_input;
}

