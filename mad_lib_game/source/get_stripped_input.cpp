#include <iostream>
#include <string>
#include <ctype.h>

std::string getStrippedInput()
{
	// Get the raw input.
	std::string inputString;
	std::getline(std::cin, inputString);


	// Becomes true once the first non-white-space character has been found.
	bool foundBody = false;

	// Once the body has been found,
	// white space is first added to this string,
	// then added to strippedString once another character is found.
	// This ensures white space at the end of the string will not be added.
	std::string whiteSpace = "";

	// The string to be returned.
	std::string strippedString = "";

	for (auto i = inputString.begin(); i != inputString.end(); ++i) {
		// If it's white space, add to whiteSpace if the body has started.
		if (std::isspace(*i)) {
			if (foundBody) {
				whiteSpace += *i;
			}
		}

		// If it's not white space, mark the body as being found,
		// add any middle white space, and add the character
		else {
			if (!foundBody) {
				foundBody = true;
			}
			if (whiteSpace.size() > 0) {
				strippedString += whiteSpace;
				whiteSpace = "";
			}
			strippedString += *i;
		}
	}

	return strippedString;
}