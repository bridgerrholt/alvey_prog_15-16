// Converts any variable to a string (doesn't fail if passed a string).

#ifndef PATCH_TO_STRING_H
#define PATCH_TO_STRING_H

#include <sstream>
#include <string>

namespace patch
{
	template <class T> std::string to_string(const T& input)
	{
		std::ostringstream stream;
		stream << input;
		return stream.str();
	}
}


#endif