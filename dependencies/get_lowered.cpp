#include <string>
#include <algorithm>

std::string getLowered(std::string inputString)
{
	std::transform(inputString.begin(), inputString.end(),
		inputString.begin(), ::tolower);
	return inputString;
}