// Terminal color codes for unix-based operating systems.

#ifndef COLOR_CODES_H
#define COLOR_CODES_H

#include <string>

#include "patch/to_string.h"

#include "convert_string.h"

class ColorCodes
{
public:
	// Bolds a string.
	template<class T>
	static std::string doB(const T& input);
	//std::string doB(const std::string& inString) const;
	// Underlines a string.
	static std::string doU(const std::string& inString);

	// Parses through HTML-style input.
	static std::string format(const std::string& inString);

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

	static std::string reset;
	static std::string bold;
	static std::string underline;

	static ColorSet regularSet;
	static ColorSet boldSet;
	static ColorSet underlineSet;
	static ColorSet backgroundSet;

private:
	// The class is meant to be purely static.
	ColorCodes();
};



template<class T>
std::string ColorCodes::doB(const T& input)
{
	return bold + patch::to_string(input) + reset;
}

#endif