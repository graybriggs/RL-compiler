

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "lexer/token.h"
#include "lexer/lexer.h"
//#include "parser/parser.h"
#include "serialization.h"

#include "parser/parser_error.h"

#include "parser/syntactic_analyzer.h"

int main(int argc, char** args) {

	if (argc < 2) {
		std::cout << "Usage: rl source.rl" << std::endl;
		return 1;
	}

	std::string source_syntax = read_source(args[1]);

	// options args[2], args[3], ..., args[n]

	std::vector<Token> tokens = lexical_analysis(source_syntax);

	std::deque<Token> td(tokens.begin(), tokens.end());

	//Parser::recursive_descent_parser(token_list);
	try {
		syntax_analysis(td);
	}
	catch (ParseException& e) {
		e.what();
	}
	//syntactic_parser(tokens);
}