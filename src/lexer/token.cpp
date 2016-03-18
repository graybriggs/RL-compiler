
#include "token.h"

std::string tokenInfo(const Token& token) {


	switch (token.type) {
		case TokenType::WHITESPACE:
			return "WHITESPACE< " + token.data + " >";
		case TokenType::KEYWORD:
			return "KEYWORD< " + token.data + " >";
		case TokenType::CONSTANT:
			return "CONSTANT< " + token.data + " >";
		case TokenType::REAL_NUMBER:
			return "REAL_NUMBER< " + token.data + " >";
		case TokenType::IDENTIFIER:
			return "IDENTIFIER< " + token.data + " >";
		case TokenType::OPERATOR_UNARY:
			return "OPERATOR_UNARY< " + token.data + " >";
		case TokenType::OPERATOR_BINARY:
			return "OPERATOR_BINARY< " + token.data + " >";
		case TokenType::OPERATOR_ASSIGNMENT:
			return "OPERATOR_ASSIGNMENT< " + token.data + " >";
		case TokenType::OPERATOR_COMPARISON:
			return "OPERATOR_COMPARISON< " + token.data + " >";
		case TokenType::COMMENT:
			return "COMMENT < " + token.data + " >";

////////// string
		case TokenType::STRING:
			return "STRING< " + token.data + " >";
		case TokenType::STRING_CONCAT:
			return "STRING_CONCAT< " + token.data + " >";

//////////////

		case TokenType::SYMBOL:
			return "SYMBOL< " + token.data + " >";
		case TokenType::L_PAREN:
			return "L_PAREN";
		case TokenType::R_PAREN:
			return "R_PAREN";
		case TokenType::ERROR:
			return "Syntax Error near: " + std::to_string(token.line) + ":" + std::to_string(token.column) + " " + token.data;
		default:
			break;
	}

	return "SPACE";
}
