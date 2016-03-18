

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>

/*

	Lexical evaluation is the second stage of the lexing process.
	The evaluator scans each token's data - or lexeme - and provides
	more detailed information on the required tokens.

	Eg. First lexer pass produces an operator token such as: OPERATOR< + >

	The second pass evaluator scans the lexeme and provides the token
	with addional meta information.

	Eg. OPERATOR< + > -> evaluator -> Symbol::BINARY_OP_ADDITION
		OPERATOR< / > -> evaluator -> Symbol::BINARY_OP_DIVISION

		KEYWORD< if > -> evaluator -> Symbol::KEYWORD_IF

	This is additional data required for syntactic analysis.

*/


struct Token;

enum Symbol {

	// Terminal symbols

	KEYWORD_VAR, // 0
	KEYWORD_WHILE, // 1
	KEYWORD_DO,  // 2
	KEYWORD_IF,  // 3
	KEYWORD_THEN,  // 4
	KEYWORD_ELSE, // 5
	KEYWORD_END, // 6
	KEYWORD_NOT, // 7

	SYMBOL_COLON,  	// 8			 // :
	SYMBOL_STR_CONCAT,  // 9         // Symbol '~' String concatenation. Will be added later

	OP_ASSIGNMENT, // 10

	BINARY_OP_ADDITION, // 11			  // +
	BINARY_OP_SUBTRACTION,	// 12 	  // --
	BINARY_OP_MULTIPLICATION, // 13   // *
	BINARY_OP_DIVISION,	// 14	  // /
	BINARY_OP_MODULO,	// 15	  // %

	COMPARISON_OP_LESS_THAN, // 16     // <
	COMPARISON_OP_GREATER_THAN, // 17  // >
	COMPARISON_OP_EQUAL_TO,   // 18    // ==
	COMPARISON_OP_NOT_EQUAL_TO, // 19  // !=


	// same as tokens
	SYM_WHITESPACE, // 20
	SYM_PARENTHESIS_LEFT,  // 21
	SYM_PARENTHESIS_RIGHT,  // 22

	// strings
	SYM_STRING,     // 23
	SYM_STRING_CONCAT,  // 24

	// Non-terminal symbols

	SYM_IDENTIFIER, // 25
	SYM_CONSTANT, // 26
	SYM_REAL_NUMBER, // 27
	SYM_COMMENT, // 28

	SYM_UNSET, // 29
	SYM_END	 // 30	// used for when there are no more tokens to be read
};

Symbol determine_keyword(const Token& tok);
Symbol determine_symbol(const Token& tok);
Symbol determine_binary_op(const Token& tok);
Symbol determine_comparison_op(const Token& tok);

std::vector<Token>& evaluate_scanned_tokens(std::vector<Token>& tokens);


#endif
