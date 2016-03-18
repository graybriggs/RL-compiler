
#include "lexer.h"

void print_source(const std::string& source) {

	std::cout << source << std::endl;
}

void print_tokens(const std::vector<Token>& tokens, TokenType exclude) {

	std::cout << "-----------------\n" << std::endl;
	std::cout << "Tokenized source: " << std::endl;
	std::cout << "Omit displaying tokens:- " << std::endl;;
	if (exclude == TokenType::NONE)
		std::cout << "\tNone" << std::endl;
	else if (exclude == TokenType::WHITESPACE)
		std::cout << "\tWHITESPACE<   >\n\tWHITESPACE< \\n >\n\tWHITESPACE< \\t >" << std::endl;
	else if (exclude == TokenType::COMMENT)
		std::cout << "\tComment" << std::endl;

	std::cout << "\n\nL:C" << "\t" << "Token type< lexeme >" << std::endl;
	std::cout << "---" << "\t" << "--------------------" << std::endl;
	for (auto& t : tokens) {
		if (exclude == t.type)
			continue;
		
		std::cout << t.line << ":" << t.column << "\t" << tokenInfo(t) << std::endl;
	}
}


std::vector<Token> strip_unnecessary(const std::vector<Token>& tokens) {

	std::vector<Token> stripped;
	unsigned count = 0;

	for (auto& token : tokens) {

		if (token.type == TokenType::WHITESPACE || token.type == TokenType::COMMENT) {
			++count;
			continue;
		}

		stripped.push_back(token);
	}

	std::cout << "\n\nRemoving unnecessary tokens." << std::endl;
	std::cout << "Removed " << count << " tokens. New tokens size: " << stripped.size() << "\n" << std::endl;
	return stripped;
}

std::vector<Token> lexical_analysis(const std::string& src) {

	std::vector<Token> tokens;
	print_source(src);
	tokens = scanner(src);
	print_tokens(tokens, TokenType::WHITESPACE);

	tokens = evaluate_scanned_tokens(tokens);

	std::vector<Token> stripped_tokens = strip_unnecessary(tokens); // remove all comments and whitespace tokens.

	return stripped_tokens;
}