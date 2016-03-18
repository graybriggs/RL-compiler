
#include "evaluator.h"

#include "token.h"

#include <string>

Symbol determine_keyword(const Token& tok) {

	const std::string& data = tok.data;

	if (data == "var")        return Symbol::KEYWORD_VAR;
	else if (data == "while") return Symbol::KEYWORD_WHILE;
	else if (data == "do")    return Symbol::KEYWORD_DO;
	else if (data == "if")    return Symbol::KEYWORD_IF;
	else if (data == "then")  return Symbol::KEYWORD_THEN;
	else if (data == "else")  return Symbol::KEYWORD_ELSE;
	else if (data == "end")   return Symbol::KEYWORD_END;
	else if (data == "not")	  return Symbol::KEYWORD_NOT;
	else throw -1; // throw UnrecognizedKeywordError(data);
}

Symbol determine_symbol(const Token& tok) {

	const std::string& data = tok.data;

	if (data == ":")      return Symbol::SYMBOL_COLON;
	else if (data == "~") return Symbol::SYM_STRING_CONCAT;
	else throw -1; // throw UnrecognizedSymbolError(data);
}

Symbol determine_binary_op(const Token& tok) {

	const std::string& data = tok.data;

	if (data == "+")      return Symbol::BINARY_OP_ADDITION;
	else if (data == "-") return Symbol::BINARY_OP_SUBTRACTION;
	else if (data == "*") return Symbol::BINARY_OP_MULTIPLICATION;
	else if (data == "/") return Symbol::BINARY_OP_DIVISION;
	else if (data == "%") return Symbol::BINARY_OP_MODULO;
	else throw -1; // throw

}

Symbol determine_comparison_op(const Token& tok) {

	const std::string& data = tok.data;

	if (data == "<")       return COMPARISON_OP_LESS_THAN;
	else if (data == ">")  return COMPARISON_OP_GREATER_THAN;
	else if (data == "==") return COMPARISON_OP_EQUAL_TO;
	else if (data == "<>") return COMPARISON_OP_NOT_EQUAL_TO;
	else throw -1; // throw
}


std::vector<Token>& evaluate_scanned_tokens(std::vector<Token>& tokens) {

	for (auto& token : tokens) {

		switch (token.type) {

			case TokenType::KEYWORD:
				token.symbol = determine_keyword(token);
				break;

			case TokenType::SYMBOL:
				token.symbol = determine_symbol(token);
				break;

			case TokenType::OPERATOR_BINARY:
				token.symbol = determine_binary_op(token);
				break;

			case TokenType::OPERATOR_COMPARISON:
				token.symbol = determine_comparison_op(token);
				break;

			// no symbol data is necessary here, so the Token equivalent Symbol is assigned.

			case TokenType::OPERATOR_ASSIGNMENT:
				token.symbol = Symbol::OP_ASSIGNMENT;
				break;

			case IDENTIFIER:
				token.symbol = Symbol::SYM_IDENTIFIER;
				break;

			case CONSTANT:
				token.symbol = Symbol::SYM_CONSTANT;
				break;

			case REAL_NUMBER:
				token.symbol = Symbol::SYM_REAL_NUMBER;
				break;

			case STRING:
				token.symbol = Symbol::SYM_STRING;
				break;

			case TokenType::L_PAREN:
				token.symbol = Symbol::SYM_PARENTHESIS_LEFT;
				break;

			case TokenType::R_PAREN:
				token.symbol = Symbol::SYM_PARENTHESIS_RIGHT;
				break;

			case TokenType::WHITESPACE:
				token.symbol = Symbol::SYM_WHITESPACE;
				break;

			case TokenType::COMMENT:
				token.symbol = Symbol::SYM_COMMENT;
				break;

			default:
				break;
		}
	}

	return tokens;
}