
#include "syntactic_analyzer.h"
#include "../lexer/evaluator.h"
#include "parser_error.h"

#include <algorithm>
#include <iostream>

enum StatementType { IF, WHILE };

static std::deque<Token> symbols;
static Symbol sym;

void next_symbol() {

	if (symbols.empty()) {
		sym = Symbol::SYM_END;
	}
	else {
		sym = symbols.front().symbol;
		std::cout << "Parsing: " << sym << std::endl;
		symbols.pop_front();
	}
}


bool accept(Symbol s) {

	if (sym == s) {
		next_symbol();
		return true;
	}
	else {
		return false;
	}
}

bool expect(Symbol s) {

	if (accept(s)) {
		return true;
	}
	else {
		return false;
	}
}



void factor() {

	if (accept(Symbol::SYM_CONSTANT)) {
		;
	}
	else if (accept(Symbol::SYM_IDENTIFIER)) {
		;
	}
	else if (accept(SYM_PARENTHESIS_LEFT)) {
		expression();
		if (!expect(Symbol::SYM_PARENTHESIS_RIGHT)) {
			std::cout << "Syntax error. Parenthesis do not match" << std::endl;
			throw ParseException("Syntax Error. Parenthesis do no match.");
			//sym = Symbol::ERROR;
		}
	}

}

void term() {

	factor();

	while (sym == Symbol::BINARY_OP_MULTIPLICATION || sym == Symbol::BINARY_OP_DIVISION) {
		next_symbol();
		factor();
	}
}

void expression() {

	term();

	while (sym == Symbol::BINARY_OP_ADDITION || sym == Symbol::BINARY_OP_SUBTRACTION) {
		next_symbol();
		term();
	}
}

void assignment() {

}

void conditional_expression(StatementType stmt) {

	if (sym == Symbol::SYM_CONSTANT || sym == Symbol::SYM_IDENTIFIER) {
		next_symbol();
		std::cout << "in if: " << sym << std::endl;
		// this is bollocks.
		if (stmt == StatementType::IF) {
			if (sym == Symbol::KEYWORD_THEN)
				return;
		}
		else if (stmt == StatementType::WHILE) {
			if (sym == Symbol::KEYWORD_DO)
				return;
		}

		if (sym == Symbol::COMPARISON_OP_LESS_THAN
			|| sym == Symbol::COMPARISON_OP_GREATER_THAN
			|| sym == Symbol::COMPARISON_OP_EQUAL_TO
			|| sym == Symbol::COMPARISON_OP_NOT_EQUAL_TO) {
		
			next_symbol();
			if (sym == Symbol::SYM_CONSTANT || sym == Symbol::SYM_IDENTIFIER) {
				;
			}
			else {
				std::cout << "Ill formed conditional statement. Expecting identifier" << std::endl;
				throw ParseException("Ill formed conditional statement. Expecting identifier");
			}
		}
		else {
			throw ParseException("Ill formed if statement. Expected comparison operator.");
		}
	}
	else {
		throw ParseException("Ill formed if statement. Expected condition");
	}
}

void variable_declaration() {
	while (sym == Symbol::KEYWORD_VAR) {
		next_symbol();
		if (!accept(Symbol::SYM_IDENTIFIER)) throw ParseException("Not identifier in variable declaration");
		if (!accept(Symbol::OP_ASSIGNMENT)) throw ParseException("Not assignment operator in variable declaration");

		expression();
		std::cout << "expression accepted" << std::endl;
	}
}

void if_statement() {
	while (sym == Symbol::KEYWORD_IF) {
		next_symbol();

		if (sym == Symbol::SYM_IDENTIFIER || sym == Symbol::SYM_CONSTANT) {
			next_symbol();
			if (sym == Symbol::KEYWORD_THEN) {
				next_symbol();
				block();
				if (!expect(Symbol::KEYWORD_END))
					throw ParseException("Expected `end` on if");
			}
			else if (sym == Symbol::COMPARISON_OP_LESS_THAN
					|| sym == Symbol::COMPARISON_OP_GREATER_THAN
					|| sym == Symbol::COMPARISON_OP_EQUAL_TO
					|| sym == Symbol::COMPARISON_OP_NOT_EQUAL_TO) {

				next_symbol();

				if (sym == Symbol::SYM_IDENTIFIER || sym == Symbol::SYM_CONSTANT) {
					next_symbol();
					if (!expect(Symbol::KEYWORD_THEN))
						throw ParseException("Expected `then` on if");
					else 
						block();
				}
				else {
					throw ParseException("Expected identifier in if condition");
				}

			}
		}
	}
}

void while_statement() {
	while (sym == Symbol::KEYWORD_WHILE) {
		next_symbol();
		conditional_expression(StatementType::WHILE);
		next_symbol();
		block();
		next_symbol();
		if (!accept(Symbol::KEYWORD_END)) {
			throw ParseException("Missing end on while");
		}
	}
}

void block() {

	while (sym == Symbol::KEYWORD_VAR || sym == Symbol::KEYWORD_IF
									  || sym == Symbol::KEYWORD_WHILE) {

		variable_declaration();
		if_statement();
		while_statement();

	}
}

void program() {
	next_symbol();
	block();
}

void syntax_analysis(std::deque<Token>& t) {

	symbols = t;	

	program();

	std::cout << "\nSyntax Analysis complete.\nSyntax is well formed.\n" << std::endl;
}
