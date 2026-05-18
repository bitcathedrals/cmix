#include <iostream>

#include <parse.h>
#include <cpu/cpu.h>
#include <repl/dispatch.h>

const inline byte cmd_field = 0;
const inline byte type_field = 1;
const inline byte adr_field = 2;

const inline byte data_field = 3;

const inline byte read_parse_size = 3;
const inline byte write_parse_size = 4;

static CmdStatus exec_read(const parse_t p);
static CmdStatus exec_write(const parse_t p);

CmdStatus run_command(const parse_t p) {
    char size = p.size();

    if(size < 1) {
        std::cerr << "cmix: empty command." << std::endl;
        return CmdStatus::bad_input;
    }

    Command cmd = string_to_command(p[cmd_field]);

    if(cmd == Command::unknown) {
        std::cerr << "cmix: unknown command: " << p[cmd_field] << std::endl;
    }

    switch (cmd) {
    case Command::quit:
        return CmdStatus::ok;

    case Command::read:
        return exec_read(p);
        break;

    case Command::write:
        return exec_write(p);
        break;

    case Command::unknown:
        break;
    }

    std::cerr << "cmix unhandled command: " << p[cmd_field] << std::endl;
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
        int address = std::atoi(p[2].c_str());

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

    if (size != read_parse_size) {
        std::cerr << "cmix bad input, expected " << size
                  << "fields, instead: "  << p << std::endl;

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
           CPU.memory[address] = parse_t(data_field);

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

