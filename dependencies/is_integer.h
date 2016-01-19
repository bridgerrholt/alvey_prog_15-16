// Returns whether or not a string is an integer.

#ifndef IS_INTEGER_H
#define IS_INTEGER_H

#include <string>
#include <cstdlib>

inline bool isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
		return false;

	char* p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

#endif