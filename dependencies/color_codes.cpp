#include "color_codes.h"

#include <string>

std::string ColorCodes::reset     = "\e[0m";
std::string ColorCodes::bold      = "\e[1m";
std::string ColorCodes::underline = "\e[4m";

ColorCodes::ColorSet ColorCodes::regularSet = {
		"\e[0;30m",
		"\e[0;31m",
		"\e[0;32m",
		"\e[0;33m",
		"\e[0;34m",
		"\e[0;35m",
		"\e[0;36m",
		"\e[0;37m"
	};

ColorCodes::ColorSet ColorCodes::boldSet = {
		"\e[1;30m",
		"\e[1;31m",
		"\e[1;32m",
		"\e[1;33m",
		"\e[1;34m",
		"\e[1;35m",
		"\e[1;36m",
		"\e[1;37m"
	};

ColorCodes::ColorSet ColorCodes::underlineSet = {
		"\e[4;30m",
		"\e[4;31m",
		"\e[4;32m",
		"\e[4;33m",
		"\e[4;34m",
		"\e[4;35m",
		"\e[4;36m",
		"\e[4;37m"
	};

ColorCodes::ColorSet ColorCodes::backgroundSet = {
		"\e[40m",
		"\e[41m",
		"\e[42m",
		"\e[43m",
		"\e[44m",
		"\e[45m",
		"\e[46m",
		"\e[47m"
	};



/*std::string ColorCodes::doB(const std::string& inString) const
{
	return bold + inString + reset;
}*/



std::string ColorCodes::doU(const std::string& inString)
{
	return underline + inString + reset;
}



std::string ColorCodes::format(const std::string& inString)
{
	bool escaped = false;
	char escapeChar = '\\';

	for (auto i = inString.begin(); i != inString.end(); ++i) {
		
	}
}






