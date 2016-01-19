// Returns whether or not a string is an unsigned integer.

#ifndef IS_UNSIGNED_INTEGER_H
#define IS_UNSIGNED_INTEGER_H

#include <string>
#include <cstdlib>

inline bool isUnsignedInteger(const std::string& s)
{
	// Remove commented portion for signed integer.
	if (s.empty() || ((!isdigit(s[0])) && /*(s[0] != '-') &&*/ (s[0] != '+')))
		return false;

	char* p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

#endif