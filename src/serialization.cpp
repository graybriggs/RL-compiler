
#include "serialization.h"

std::string read_source(const std::string& filename) {

	FILE* f = fopen(filename.c_str(), "r");

	fseek(f, 0 ,SEEK_END);
	long int size = ftell(f);
	rewind(f);

	char* extracted_source = new char[size];

	fread(extracted_source, 1, size, f);

	std::string syntax(extracted_source);
	delete extracted_source;

	return syntax;
}