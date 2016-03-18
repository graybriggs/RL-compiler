
#include <iostream>
#include <string>
#include <list>

#include "../lexer/evaluator.h"
#include "../lexer/token.h"



namespace Parser {


////////////

enum SyntaxAnalysisResult { WELL_FORMED, ILL_FORMED };

void syntax_result(const SyntaxAnalysisResult result);

////

void next_token();

bool accept(Symbol sym);
bool expect(Symbol sym);
void factor();

void term();

void expression();

bool becomes();
void assignment();
void var_declaration();
void scope();
void program();

void recursive_descent_parser(std::list<Token>& tok);

} // Parser namespace