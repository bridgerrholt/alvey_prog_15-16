#ifndef PATCH_STOI_H
#define PATCH_STOI_H

#include <iostream>
#include <typeinfo>
#include <sstream>
#include <string>

namespace patch
{
	int stoi(const std::string& inputString)
	{
		std::stringstream stream(inputString);

		int outInt;
		if ((stream >> outInt).fail() || !(stream >> std::ws).eof()) {
			throw std::bad_cast();
		}
	}
}

#endif