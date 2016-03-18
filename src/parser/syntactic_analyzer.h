
#ifndef SYNTACTIC_ANALYZER_H
#define SYNTACTIC_ANALYZER_H

#include "../lexer/token.h"
#include "../lexer/evaluator.h"

#include <deque>


void next_symbol();

bool accept();
bool expect();

void factor();
void term();
void expression();
void assignment();
void conditional_expression();
void variable_declaration();
void if_statement();
void while_statement();
void block();

void program();
void syntax_analysis(std::deque<Token>&);


#endif