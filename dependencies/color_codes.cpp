#include "color_codes.h"

#include <string>

ColorCodes::ColorCodes()
{
	reset     = "\e[0m";
	bold      = "\e[1m";
	underline = "\e[4m";

	regularSet = {
		"\e[0;30m",
		"\e[0;31m",
		"\e[0;32m",
		"\e[0;33m",
		"\e[0;34m",
		"\e[0;35m",
		"\e[0;36m",
		"\e[0;37m"
	};

	boldSet = {
		"\e[1;30m",
		"\e[1;31m",
		"\e[1;32m",
		"\e[1;33m",
		"\e[1;34m",
		"\e[1;35m",
		"\e[1;36m",
		"\e[1;37m"
	};

	underlineSet = {
		"\e[4;30m",
		"\e[4;31m",
		"\e[4;32m",
		"\e[4;33m",
		"\e[4;34m",
		"\e[4;35m",
		"\e[4;36m",
		"\e[4;37m"
	};

	backgroundSet = {
		"\e[40m",
		"\e[41m",
		"\e[42m",
		"\e[43m",
		"\e[44m",
		"\e[45m",
		"\e[46m",
		"\e[47m"
	};
}