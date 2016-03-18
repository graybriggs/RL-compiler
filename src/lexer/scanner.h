
#ifndef SCANNER_H
#define SCANNER_H


#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "token.h"

std::string getAtom(const std::string& syntax, std::uint32_t position);
bool is_constant(const std::string& syntax);
bool is_real_number(const std::string& syntax);
bool is_keyword(const std::string& atom);
bool is_string(const std::string& atom);
bool is_assignment_operator(const std::string& atom);
bool is_double_comparison(const std::string& atom);
bool is_less_than_operator(const std::string& atom);
bool is_greater_than_operator(const std::string& atom);
bool is_valid_identifier(const std::string& atom);
bool is_whitespace(const char c);
bool is_comment(const char c);
std::uint32_t extract_comment(const std::string& syntax, std::uint32_t pos);
std::vector<Token> scanner(const std::string& syntax);

#endif