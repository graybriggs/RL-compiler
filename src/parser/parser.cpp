
#include "parser.h"
#include "../lexer/token.h"

#include "parser_error.h"

std::list<Token> tokens;
Symbol cur_sym;

void Parser::syntax_result(const Parser::SyntaxAnalysisResult result) {

	std::string res_str = (result == WELL_FORMED) ? "well formed" : "ill formed";

	std::cout << "Syntax analysis result: " << res_str << " syntax." << std::endl;
}

void Parser::next_token() {

	while (tokens.size() > 0) {
		//cur_sym = tokens[token_num].symbol;

		Token t = tokens.front();
		tokens.pop_front();
		cur_sym = t.symbol;
		std::cout << "Analyzing token" << std::endl;
		std::cout << "Data: " << t.data  << "\n" << std::endl;		
	}
}

bool Parser::accept(Symbol sym) {
	if (cur_sym == sym) {
		next_token();
		return true;
	}
	else
		return false;
}

bool Parser::expect(Symbol sym) {
	if (accept(sym)) {
		return true;
	}
	else {
		std::cout << "Unexpected symbol" << std::endl;
		return false;
	}	
}


void Parser::factor() {
	if (accept(Symbol::SYM_CONSTANT))
		;
	else if (accept(Symbol::SYM_IDENTIFIER))
		;
	else if (accept(Symbol::SYM_PARENTHESIS_LEFT)) {
		Parser::expression();
		expect(Symbol::SYM_PARENTHESIS_RIGHT);
	}
	else {
		std::cout << "here" << std::endl;
		//std::cout << "factor() - expected SYM_CONSTANT, got: " << cur_sym << std::endl;
		throw ParseException("Unexpected symbol. Excepted SYM_CONSTNANT, got ");
	}
}

void Parser::term() {
	factor();

	while (cur_sym == Symbol::BINARY_OP_MULTIPLICATION || cur_sym == Symbol::BINARY_OP_DIVISION) {
		next_token();
		factor();
	}
}

void Parser::expression() {
	term();

	while (cur_sym == Symbol::BINARY_OP_ADDITION || cur_sym == Symbol::BINARY_OP_SUBTRACTION) {
		next_token();
		term();
	}
}

bool Parser::becomes() {

	return expect(Symbol::OP_ASSIGNMENT);
}

void Parser::assignment() {

	if (!accept(Symbol::SYM_IDENTIFIER))
		std::cout << "Ill formed assignment" << std::endl;
	if (!becomes())
		std::cout << "Ill formed assignment" << std::endl;
	
	expression();
}

void Parser::var_declaration() {

	if (accept(Symbol::KEYWORD_VAR)) {
		if (!expect(Symbol::SYM_IDENTIFIER))
			std::cout << "Ill formed variable declaration" << std::endl;

		if (cur_sym == Symbol::OP_ASSIGNMENT) { // update this later for other types
			next_token();
			expression();
		}
	}	
}

void Parser::scope() {
	//expression();
	//assignment();
	while (cur_sym == Symbol::KEYWORD_VAR)
		var_declaration();
}

void Parser::program() {
	scope();
}

void Parser::recursive_descent_parser(std::list<Token>& tok) {

	tokens = tok;
	next_token();
	program();

	Parser::SyntaxAnalysisResult result = Parser::SyntaxAnalysisResult::WELL_FORMED;

	syntax_result(result);
}
