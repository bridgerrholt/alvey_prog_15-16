#include <math.h>
#include <exception>

#include <iostream>
#include <string>

#include <get_stripped_input.h>
#include <is_integer.h>
#include <constants.h>

#include "manager.h"

extern const ColorCodes G_COLOR_CODES;

Manager::Manager() : guessCount_(0)
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

		// If the maximum is the minimum, that's the answer.
		if (difference_ == 0) {
			answer = min_;
			break;
		}

		// Otherwise, guess again.
		makeGuess();

	}

	// Display their answer and the amount of guesses.
	// Only be plural if multiple guesses.
	std::string guessString = "guess";
	if (guessCount_ > 1)
		guessString += "es";

	std::cout << "\nYour number is " <<
		constants::G_COLOR_CODES.bold << answer <<
		constants::G_COLOR_CODES.reset << "! (took " <<
		guessCount_ << " " << guessString << ")\n";
}



void Manager::makeGuess()
{
	// Increment the guess counter.
	++guessCount_;

	// Pick the number directly in the middle.
	Number guess = min_ + floor(difference_/2.0);

	// If this is their first time,
	// ask if it's greater than or less than their number.
	if (guessCount_ == 1) {
		std::cout << "Is " <<
			constants::G_COLOR_CODES.bold << guess <<
			constants::G_COLOR_CODES.reset <<
			" greater than, less than, or equal to your number? (> < =):\n";
	}

	while (true) {
		// Reset the fail_ flag, it may be used.
		resetFail();

		// Get the input.
		std::cout <<
			constants::G_COLOR_CODES.bold << guess <<
			constants::G_COLOR_CODES.reset << " is ";
		std::string strippedInput = getStrippedInput();

		if (strippedInput == ">") {
			max_ = guess-1;
		}
		else if (strippedInput == "<") {
			min_ = guess+1;
		}
		else if (strippedInput == "=") {
			min_ = guess;
			max_ = guess;
		}

		// Fail if not > < =.
		else {
			// Fail if no data inputted.
			if (strippedInput == "") {
				makeError("Must have an input.");
				continue;
			}

			makeError("Must be '>', '<', or '='.");
			continue;
		}

		break;
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




