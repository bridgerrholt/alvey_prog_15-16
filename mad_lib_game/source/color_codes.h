// Terminal color codes for unix-based operating systems.

#ifndef COLOR_CODES_H
#define COLOR_CODES_H

#include <string>

class ColorCodes
{
public:
	ColorCodes();

	// A set of colors for different kinds of codes.
	class ColorSet
	{
	public:
		std::string black;
		std::string red;
		std::string green;
		std::string yellow;
		std::string blue;
		std::string purple;
		std::string cyan;
		std::string white;
	};

	std::string reset;
	std::string bold;
	std::string underline;

	ColorSet regularSet;
	ColorSet boldSet;
	ColorSet underlineSet;
	ColorSet backgroundSet;
};

#endif