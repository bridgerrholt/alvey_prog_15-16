#include "manager.h"

#include <math.h>
#include <exception>

#include <iostream>
#include <string>

#include <input_handler.h>
#include <get_stripped_input.h>
#include <is_integer.h>
#include <constants.h>

#include <patch/stoi.h>
#include <patch/to_string.h>

using namespace binary_search;

Manager::Manager(const explorer::Manager& baseManager) :
	explorer::Manager(baseManager)
{
	reset();
}



void Manager::run() {
	reset();

	// Ask for the range.
	inputHandler_.printQuestion("Enter the range (min,max):");
	std::string strippedInput;

	// Repeat if failed.
	while (true) {
		// Get the input.
		strippedInput = inputHandler_.askStripped("", std::size_t(1));

		std::string minString = "";
		std::string maxString = "";

		bool foundDivisor = false;
		fail_.reset();

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
			fail_.error("Must have a divisor.");
			continue;
		}

		// Fail if missing a value.
		checkEmptyValue(minString, "minimum");
		checkEmptyValue(maxString, "maximum");
		if (fail_.get()) continue;

		// Fail if the values aren't integers.
		checkValueInteger(minString, "minimum");
		checkValueInteger(maxString, "maximum");
		if (fail_.get()) continue;

		// Fail if a value is too small or too large for the Number type.
		min_ = valueToNumber(minString, "minimum");
		max_ = valueToNumber(maxString, "maximum");
		if (fail_.get()) continue;

		// Fail if the minimum value is not less than the maximum value.
		if (min_ >= max_) {
			fail_.error("The minimum value must be less than the maximum value.");
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

	//std::cout << ColorCodes::doB("ABC\n");

	std::cout << "\nYour number is " <<
		ColorCodes::doB(patch::to_string(answer)) << "! (took " <<
		guessCount_ << " " << guessString << ")\n";
}



void Manager::reset()
{
	guessCount_ = 0;
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
			ColorCodes::doB(patch::to_string(guess)) <<
			" greater than, less than, or equal to your number? (> < =):\n";
	}

	// Execute once, continue to if the fail_ flag is true.
	do {
		// Reset the fail_ flag, it is used.
		fail_.reset();

		// Get the input.
		std::cout << ColorCodes::doB(patch::to_string(guess)) << " is ";
		std::string strippedInput = getStrippedInput();

		// Their number is greater than the guessed number.
		if (strippedInput == ">") {
			// If the guess is the minimum value,
			// it can't be greater than the actual number.
			if (guess == min_)
				fail_.error("This guess is the minimum.");

			else
				// Since our maximum was too high, set it lower.
				max_ = guess-1;
		}

		// Their number is less than the guessed number.
		else if (strippedInput == "<") {
			// If the guess is the maximum value,
			// it can't be less than the actual number.
			if (guess == max_)
				fail_.error("This guess is the maximum.");
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
				fail_.error("Must have an input.");

			// Otherwise fail if something else.
			else
				fail_.error("Must be '>', '<', or '='."); 
		}
	} while (fail_.get());
}



void Manager::checkEmptyValue(std::string input, std::string name)
{
	if (input == "") {
		fail_.error("Must have a " + name + " value.");
	}
}



void Manager::checkValueInteger(std::string input, std::string name)
{
	if (!isInteger(input)) {
		fail_.error("Value " + name + " must be an integer.");
	}
}



Manager::Number Manager::valueToNumber(std::string input, std::string name)
{
	Number returnNum;
	try {
		returnNum = patch::stoi(input);
	}
	catch (std::exception& e) {
		fail_.error("The " + name + " value is out of range.");
	}

	return returnNum;
}



void Manager::calculateDifference()
{
	difference_ = max_ - min_;
}




