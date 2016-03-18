cmake_minimum_required(VERSION 2.6)
project(rudementary_langauge)

ADD_DEFINITIONS ( -Wall -std=c++11 -g -lm )


include_directories("{PROJECT_SOURCE_DIR}/lexer")	
include_directories("{PROJECT_SOURCE_DIR}/parser")

add_executable(rl.out
	evaluator.cpp
	lexer.cpp
	scanner.cpp
	token.cpp
	parse_error.cpp
	parser.cpp
	semantic_analyzer.cpp
	syntactic_analyzer.cpp
	symbol_table.cpp
	serialiazation.cpp
	)



