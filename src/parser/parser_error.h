

#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <exception>
#include <string>

class ParseException : public std::exception {
public:

	explicit ParseException(const std::string& msg);
	virtual ~ParseException();

	virtual const char* what() const noexcept;

protected:
	std::string msg_;

};


#endif