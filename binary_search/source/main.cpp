#include <iostream>
#include <exception>
#include <vector>
#include <queue>

#include <get_stripped_input.h>
#include <is_unsigned_integer.h>
#include <rand_range.h>

#include "manager.h"

int main(int argc, char* argv[])
{
	/*// Ask for the range.
	std::cout << "Enter the range (min-max):\n ";
	std::string strippedInput = getStrippedInput();


	std::cout << "Integer greater than 1:\n ";
	std::string strippedInput = getStrippedInput();
	typedef unsigned long int IntType;
	IntType intInput;

	while (true) {
		if (isUnsignedInteger(strippedInput)) {
			try {
				intInput = std::stoi(strippedInput);
			}
			catch (std::exception& e) {
				std::cout << "Too large.";
			}

			if (intInput > 1) {
				break;
			}
		}
		else {
			std::cout << "Must be a positive whole number.";
		}

		std::cout << "\n ";
		strippedInput = getStrippedInput();
	}

	// Make a list size of intInput.
	std::cout << "Making a list of length n (" << intInput <<
		") of random numbers from 0 to n.\n";
	std::priority_queue<IntType> intList;

	for (std::size_t i = 0; i < intInput; ++i) {
		intList.push(randRange(0, intInput));
	}

	// Ask for a number to find.
	std::cout << "Positive integer between 0 and " <<
		intInput << " (exclusive):\n ";
	strippedInput = getStrippedInput();
	IntType toFind;

	while (true) {
		if (isUnsignedInteger(strippedInput)) {
			try {
				toFind = std::stoi(strippedInput);
			}
			catch (std::exception& e) {
				std::cout << "Too large.";
			}

			if (toFind < intInput) {
				break;
			}
			else {
				std::cout << "Too large.";
			}
		}
		else {
			std::cout << "Must be a positive whole number.";
		}

		std::cout << "\n ";
		strippedInput = getStrippedInput();
	}

	// Find the number.*/

	while (true) {
		Manager manager;
	}


	// Exit.
	return 0;
}