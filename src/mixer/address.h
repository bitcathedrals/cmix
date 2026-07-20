#ifndef MIXER_ADDRESS_H
#define MIXER_ADDRESS_H

#include "mixer/parser.h"

std::unique_ptr<Token> build_signed_number_parser(void);
std::unique_ptr<Token> build_field_parser(void);
std::unique_ptr<Token> build_comma_index_field_parser(void);
std::unique_ptr<Token> build_comma_index_parser(void);

std::unique_ptr<Token> build_address_parser(void);

#endif
