

#ifndef LEXER_H
#define LEXER_H

#include "evaluator.h"
#include "scanner.h"
#include "token.h"

#include <iostream>
#include <string>
#include <vector>

void print_source(const std::string& source);
void print_tokens(const std::vector<Token>& tokens, TokenType exclude);
std::vector<Token> strip_unnecessary(const std::vector<Token>&);
std::vector<Token> lexical_analysis(const std::string& src);


#endif