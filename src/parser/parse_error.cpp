
#include "parser_error.h"

ParseException::ParseException(const std::string& msg)
	: msg_(msg) {}

ParseException::~ParseException()
{}

const char* ParseException::what() const noexcept {
	return msg_.c_str();
}