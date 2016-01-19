#include <exception>

#include <iostream>
#include <string>

#include <get_stripped_input.h>
#include <is_integer.h>

#include "manager.h"

Manager::Manager()
{
	// Ask for the range.
	std::cout << "Enter the range (min,max):\n";
	std::string strippedInput;

	// Repeat if failed.
	while (true) {
		// Get the input.
		std::cout << " ";
		strippedInput = getStrippedInput();

		std::string minString = "";
		std::string maxString = "";

		bool foundDivisor = false;
		resetFail();

		// Parse through, fail if ',' is not found.
		for (auto i = strippedInput.begin(); i != strippedInput.end(); ++i) {
			// If ',' hasn't been found yet, look for it and,
			// if it's not found, add to minString.
			if (!foundDivisor) {
				// If it's not the first
				if (*i == ',') {
					foundDivisor = true;
				}
				else {
					minString += *i;
				}
			}
			// If ',' has been found, add to maxString.
			else {
				maxString += *i;
			}
		}

		// Fail if no ',' was found.
		if (!foundDivisor) {
			makeError("Must have a divisor.");
			continue;
		}

		// Fail if missing a value.
		if (minString == "") {
			makeError("Must have a minimum value.");
		}

		if (maxString == "") {
			makeError("Must have a maximum value.");
		}

		if (fail_) continue;

		// Fail if the values aren't integers.
		if (!isInteger(minString)) {
			makeError("Minimum value must be an integer.");
		}

		if (!isInteger(maxString)) {
			makeError("Maximum value must be an integer.");
		}

		if (fail_) continue;

		// Fail if a value is too small or too large for the Number type.
		try {
			min_ = std::stoi(minString);
		}
		catch (std::exception& e) {
			makeError("Minimum value is out of range.");
		}

		try {
			max_ = std::stoi(maxString);
		}
		catch (std::exception& e) {
			makeError("Maximum value is out of range.");
		}

		if (fail_) continue;

		// Fail if the minimum value is not less than the maximum value.
		if (min_ >= max_) {
			makeError("Minimum value must be less than maximum value.");
			continue;
		}

		break;
	}

	Number answer;
	while (true) {
		// Set difference_.
		calculateDifference();

		// If no difference, give the answer.
		if (difference_ == 0) {
			answer = min_;
			break;
		}

	}
}



void Manager::makeGuess()
{
	// Ask for the guess.
	std::cout << "Make a guess:\n";
	std::string strippedInput;

	while (true) {
		// Get the input.
		std::cout << " ";
		strippedInput = getStrippedInput();

		resetFail();

		// Fail if no data inputted.
		if (strippedInput == "") {
			makeError("Must have a value.");
			continue;
		}
	}
}



void Manager::makeError(const std::string& errorString)
{
	std::cout << errorString << '\n';
	fail_ = true;
}



void Manager::resetFail()
{
	fail_ = false;
}




void Manager::calculateDifference()
{
	difference_ = max_ - min_;
}




