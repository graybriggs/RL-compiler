
#include <cctype>
#include <cstdint>
#include <iostream>

#include "scanner.h"
#include "token.h"


std::string getAtom(const std::string& syntax, std::uint32_t position) {

	unsigned num = 0;
	for (unsigned i = position; i < syntax.length(); ++i) {
		if (std::isalnum(syntax[i]) || syntax[i] == '_'
								    || syntax[i] == '.'
								    || syntax[i] == '"'
								    || syntax[i] == '>'
								    || syntax[i] == '<'
								    || syntax[i] == '=')
			num++;
		else
			break;
	}
	return syntax.substr(position, num);
}

bool is_constant(const std::string& atom) {

	for (unsigned i = 0; i < atom.length(); ++i) {
		if (!std::isdigit(atom[i])) {
			return false;
		}
	}
	return true;
}

bool is_real_number(const std::string& atom) {

	// finds decimal point then checks for numbers either side

	for (unsigned i = 0; i < atom.length(); ++i) {
		if (atom[i] == '.') {
			if ((atom.substr(0, i).length() > 0) && (atom.substr(i + 1, atom.length()).length() > 0)) {

				if (is_constant(atom.substr(0, i)) && is_constant(atom.substr(i + 1, atom.length())))
					return true;
				else
					return false;
			}
		}
	}
  return false;
}

bool is_keyword(const std::string& atom) {
	return (atom == "var" || atom == "if"
					  || atom == "then"
					  || atom == "do"
					  || atom == "else"
					  || atom == "end"
					  || atom == "while"
					  || atom == "not");
}

bool is_string(const std::string& atom) {

	 return (atom[0] == '"' && atom[atom.length() - 1] == '"');
}

bool is_assignment_operator(const std::string& atom) {

	return (atom.length() == 1 && atom[0] == '=');
}

bool is_double_comparison(const std::string& atom) {

	return ((atom[0] == '=' && atom[1] == '=')
	 || (atom[0] == '<' && atom[1] == '>'));
}

bool is_less_than_operator(const std::string& atom) {

	return (atom.length() == 1 && atom[0] == '<');
}

bool is_greater_than_operator(const std::string& atom) {

	return (atom.length() == 1 && atom[0] == '>');
}

bool is_valid_identifier(const std::string& atom) {

	return (std::isalpha(atom[0]) || atom[0] == '_');
}

bool is_whitespace(const char c) {

	return (c == ' ' || c == '\n' || c == '\t');
}

bool is_comment(const char c) {

	return (c == '#');
}

// Input: source code string, postion of the starting # of the comment
// Output: length of comment from # to '\n' (single line comments)
std::uint32_t extract_comment(const std::string& syntax, std::uint32_t pos) {

	std::uint32_t i = pos;
	while (syntax[i] != '\n')
		++i;

	return i - pos;
}

std::vector<Token> scanner(const std::string& syntax) {

	int line = 0;
	int column = 0;

	std::vector<Token> tokens;

	for (std::uint32_t i = 0; i < syntax.length(); ) {

		switch (syntax[i]) {
			case '(': {
				tokens.push_back(Token("(", TokenType::L_PAREN, line, column));
				++i;
				break;
			}
			case ')': {
				tokens.push_back(Token(")", TokenType::R_PAREN, line, column));
				++i;
				break;
			}
			case '+': {
				tokens.push_back(Token("+", TokenType::OPERATOR_BINARY, line, column));
				++i;
				break;
			}
			case '-': {
				tokens.push_back(Token("-", TokenType::OPERATOR_BINARY, line, column));
				++i;
				break;
				}
			case '*': {
				tokens.push_back(Token("*", TokenType::OPERATOR_BINARY, line, column));
				++i;
				break;
			}
			case '/': {
				tokens.push_back(Token("/", TokenType::OPERATOR_BINARY, line, column));
				++i;
				break;
			}
			case '%': {
				tokens.push_back(Token("%", TokenType::OPERATOR_BINARY, line, column));
				++i;
				break;
			}
			case ':': {
				tokens.push_back(Token(":", TokenType::SYMBOL, line, column));
				++i;
				break;
			}
			case '~': {
				tokens.push_back(Token("~", TokenType::STRING_CONCAT, line, column));
			}

			default: {
				if (is_whitespace(syntax[i])) {
					tokens.push_back(Token(std::to_string(syntax[i]), TokenType::WHITESPACE, line, column));
					if (syntax[i] == '\n'){
						column = 0;
						line++;
						i++;
					}
					else if (syntax[i] == '\t') {
						column += 2;
						i++;
					}
					else {
						i++;
						column++;
					}
				}
				else if (is_comment(syntax[i])) {
					std::uint32_t len = extract_comment(syntax, i);
					tokens.push_back(Token(syntax.substr(i, len), TokenType::COMMENT, line, column));
					i += len;
					column += len;
				}
				else {
					std::string atom = getAtom(syntax, i);

					if (atom == "") {
						tokens.push_back(Token(atom, TokenType::ERROR, line, column));
						return tokens;
					}
					else if (is_string(atom)) {
						tokens.push_back(Token(atom, TokenType::STRING, line, column));
					}
					else if (is_real_number(atom)) {
						if (is_real_number(atom))
							tokens.push_back(Token(atom, TokenType::REAL_NUMBER, line, column));
					}
					else if (is_constant(atom)) {
						tokens.push_back(Token(atom, TokenType::CONSTANT, line, column));
					}
					else if (is_keyword(atom)) {
						tokens.push_back(Token(atom, TokenType::KEYWORD, line, column));
					}
					else if (is_assignment_operator(atom)) {
						tokens.push_back(Token("=", TokenType::OPERATOR_ASSIGNMENT, line, column));
					}
					else if (is_double_comparison(atom)) {
						tokens.push_back(Token(atom, TokenType::OPERATOR_COMPARISON, line, column));
					}
					else if (is_less_than_operator(atom)) {
						tokens.push_back(Token("<", TokenType::OPERATOR_COMPARISON, line, column));
					}
					else if (is_greater_than_operator(atom)) {
						tokens.push_back(Token(">", TokenType::OPERATOR_COMPARISON, line, column));
					}
					else {
						if (is_valid_identifier(atom))
							tokens.push_back(Token(atom, TokenType::IDENTIFIER, line, column));
						else
							tokens.push_back(Token(atom, TokenType::ERROR, line, column));

					}
					i += atom.length();
					column += atom.length();
				}
			}
		}	
	}
	return tokens;
}