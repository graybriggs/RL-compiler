

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "evaluator.h"



enum TokenType {

	WHITESPACE,
	L_PAREN,
	R_PAREN,
	OPERATOR_UNARY,
	OPERATOR_BINARY,
	OPERATOR_COMPARISON,
	OPERATOR_ASSIGNMENT,
	SYMBOL,
	KEYWORD,
	IDENTIFIER,
	CONSTANT, // remove
	REAL_NUMBER,
	NUMBER,
	STRING,
	STRING_CONCAT,
	COMMENT,
	ERROR,

	NONE // used for printing
};


struct Token {

	Token(const std::string& id, TokenType tt, unsigned l, unsigned col)
		: data(id), type(tt), line(l), column(col), symbol(Symbol::SYM_UNSET) {}

	
	std::string data;  // the actual data of the token
	TokenType type;	   // the determined type of token
	unsigned line;     // the line number that the token appeard in the source file
	unsigned column; // token's column in the source file
	Symbol symbol;
};

std::string tokenInfo(const Token& token);


#endif