#include "input_handler.h"

#include <iostream>
#include <ctype.h>

std::string InputHandler::defaultQuestion_ = "";
std::string InputHandler::defaultEnding_ = "";

std::string InputHandler::getRawInput()
{
	// Get the raw input.
	std::string inputString;
	std::getline(std::cin, inputString);

	// Return the unformatted string.
	return inputString;
}

std::string InputHandler::getRawInput(
	const std::string& question,
	const std::string& ending,
	bool useDefaultEnding)
{
	askQuestion(question, ending, useDefaultEnding);
	return getRawInput();
}

std::string InputHandler::getRawInput(
	const std::string& question,
	bool useDefaultEnding)
{
	askQuestion(question, "", useDefaultEnding);
	return getRawInput();
}



std::string InputHandler::getStrippedInput()
{
	// Get the raw input.
	std::string inputString = getRawInput();

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

std::string InputHandler::getStrippedInput(
	const std::string& question,
	bool useDefaultEnding)
{
	askQuestion(question, "", useDefaultEnding);
	return getStrippedInput();
}

std::string InputHandler::getStrippedInput(
	const std::string& question,
	const std::string& ending,
	bool useDefaultEnding)
{
	askQuestion(question, ending, useDefaultEnding);
	return getStrippedInput();
}



void InputHandler::setDefaultQuestion(const std::string& defaultQuestion)
{
	defaultQuestion_ = defaultQuestion;
}


void InputHandler::setDefaultEnding(const std::string& defaultEnding)
{
	defaultEnding_ = defaultEnding;
}



void InputHandler::askQuestion(
	const std::string& question,
	const std::string& ending,
	bool useDefaultEnding)
{
	std::cout << question;

	if (useDefaultEnding) {
		std::cout << defaultEnding_;
	}
	else {
		std::cout << ending;
	}
}








