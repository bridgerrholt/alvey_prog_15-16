#include <math.h>
#include <exception>

#include <iostream>
#include <string>

#include <get_stripped_input.h>
#include <is_integer.h>
#include <constants.h>

#include <patch/stoi.h>
#include <patch/to_string.h>

#include "manager.h"

extern const ColorCodes constants::G_COLOR_CODES;

using namespace constants;

Manager::Manager() : guessCount_(0), fail_(false)
{

}



void Manager::run() {
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
			// If ',' hasn't been found yet, look for it and
			// if it's not found add to minString.
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
		checkEmptyValue(minString, "minimum");
		checkEmptyValue(maxString, "maximum");
		if (fail_) continue;

		// Fail if the values aren't integers.
		checkValueInteger(minString, "minimum");
		checkValueInteger(maxString, "maximum");
		if (fail_) continue;

		// Fail if a value is too small or too large for the Number type.
		min_ = valueToNumber(minString, "minimum");
		max_ = valueToNumber(maxString, "maximum");
		if (fail_) continue;

		// Fail if the minimum value is not less than the maximum value.
		if (min_ >= max_) {
			makeError("The minimum value must be less than the maximum value.");
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

	//std::cout << G_COLOR_CODES.doB("ABC\n");

	std::cout << "\nYour number is " <<
		G_COLOR_CODES.doB(patch::to_string(answer)) << "! (took " <<
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
			G_COLOR_CODES.doB(patch::to_string(guess)) <<
			" greater than, less than, or equal to your number? (> < =):\n";
	}

	// Execute once, continue to if the fail_ flag is true.
	do {
		// Reset the fail_ flag, it is used.
		resetFail();

		// Get the input.
		std::cout << G_COLOR_CODES.doB(patch::to_string(guess)) << " is ";
		std::string strippedInput = getStrippedInput();

		// Their number is greater than the guessed number.
		if (strippedInput == ">") {
			// If the guess is the minimum value,
			// it can't be greater than the actual number.
			if (guess == min_)
				makeError("This guess is the minimum.");

			else
				// Since our maximum was too high, set it lower.
				max_ = guess-1;
		}

		// Their number is less than the guessed number.
		else if (strippedInput == "<") {
			// If the guess is the maximum value,
			// it can't be less than the actual number.
			if (guess == max_)
				makeError("This guess is the maximum.");
			else
				// Since our minimum was too low, set it higher.
				min_ = guess+1;
		}

		// Their number is equal to the guessed number (game complete).
		else if (strippedInput == "=") {
			// Narrow in on the guess.
			min_ = guess;
			max_ = guess;
		}

		// Fail if not '>', '<', or '='.
		else {
			// Fail if no data inputted.
			if (strippedInput == "")
				makeError("Must have an input.");

			// Otherwise fail if something else.
			else
				makeError("Must be '>', '<', or '='."); 
		}
	} while (fail_);
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



void Manager::checkEmptyValue(std::string input, std::string name)
{
	if (input == "") {
		makeError("Must have a " + name + " value.");
	}
}



void Manager::checkValueInteger(std::string input, std::string name)
{
	if (!isInteger(input)) {
		makeError("Value " + name + " must be an integer.");
	}
}



Manager::Number Manager::valueToNumber(std::string input, std::string name)
{
	Number returnNum;
	try {
		returnNum = patch::stoi(input);
	}
	catch (std::exception& e) {
		makeError("The " + name + " value is out of range.");
	}

	return returnNum;
}



void Manager::calculateDifference()
{
	difference_ = max_ - min_;
}




