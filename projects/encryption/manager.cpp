#include "manager.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <algorithm>

#include <constants.h>
#include <rand_range.h>
#include <get_stripped_input.h>
#include <get_lowered.h>

#include <functional>

using namespace encryption;

Manager::Manager(const explorer::Manager& baseManager) :
	explorer::Manager(baseManager)
{

}



void Manager::run()
{
	input_ = askInput();
	std::cout << "\n";

	EncryptionMethod method = askMethod();
	std::cout << "\n";
	password_ = askPassword();
	std::cout << "\n";

	std::size_t randHash = std::hash<std::string>{}(password_);
	srand(randHash);

	std::string fileNameLabel = "input";

	for (std::size_t i = 0; i < 2; ++i) {
		std::cout << "Enter " + fileNameLabel + " file name:";
		std::string inputString;

		while (true) {
			inputString =
				inputHandler_.askStripped("", true, std::size_t(1));

			if (inputString == "") {
				std::cout << "Invalid input.";
			}
			else {
				break;
			}

		}

		std::string fileName = "projects/encryption/files/" + inputString;
		if (i == 0) {
			inputFileName_ = fileName;
			fileNameLabel = "ouput";
		}
		else {
			outputFileName_ = fileName;
		}
	};
	std::cout << "in: " << inputFileName_ << '\n';
	std::cout << "out: " << outputFileName_ << '\n';

	try {
		inFile_.open(inputFileName_.c_str(),
			std::ios_base::binary);
		outFile_.open(outputFileName_,
			std::ios_base::binary);
	}
	catch (std::exception& e) {
		std::cout << e.what();
		return;
	}


	switch (method) {
	case CAESARIAN:
		runCaesarian();
		break;

	case PSEUDO_RANDOM:
		runPseudoRandom();
		break;

	case SUBSTITUTION:
		runSubstitution();
		break;
	}

	inFile_.close();
	outFile_.close();


}



Manager::InputChoice Manager::askInput()
{
	std::cout <<
		"[E]ncrypt\n"
		"[D]ecrypt\n\n"

		"What would you like to do?";

	while (true) {
		std::string input =
			getLowered(inputHandler_.askStripped());

		if (input == "e" || input == "encrypt") {
			return ENCRYPT;
		}
		else if (input == "d" || input == "decrypt") {
			return DECRYPT;
		}
		else {
			std::cout << "Invalid input.";
		}
	}
}



Manager::EncryptionMethod Manager::askMethod()
{
	std::cout <<
		"[C]aesarian fixed offset\n"
		"[P]seudo-random offset\n"
		"[S]ubstitution cipher\n\n"

		"Which method?";

	while (true) {
		std::string input =
			getLowered(inputHandler_.askStripped());

		if (input == "c" || input == "caesarian") {
			return CAESARIAN;
		}
		else if (input == "p" || input == "pseudo-random") {
			return PSEUDO_RANDOM;
		}
		else if (input == "s" || input == "substitution") {
			return SUBSTITUTION;
		}
		else {
			std::cout << "Invalid input.";
		}
	}
}



std::string Manager::askPassword()
{
	std::cout << "Password:";
	std::string input =
		getLowered(inputHandler_.askRaw());

	while (true) {
		if (input == "") {
			std::cout << "Invalid input.";
		}
		else {
			return input;
		}
	}
}



int Manager::getOffset(bool isDecrypting)
{
	// Margins of 10 to make it harder to visually catch on to.
	int offset = randRange(10, 246);

	// Go the opposite way for decryptions.
	if (isDecrypting)
		offset = -offset;

	return offset;
}



void Manager::runCaesarian()
{
	int offset = getOffset(input_ == DECRYPT);
	std::cout << "Using the offset of " << offset << '\n';

	// For each character, add the offset to its binary representation.
	char currentChar;
	while (inFile_ >> std::noskipws >> currentChar) {
		outFile_ << char(((unsigned char)currentChar)+offset);
	}
}



void Manager::runPseudoRandom()
{
	// For each character, add a new offset to its binary representation.
	char currentChar;
	while (inFile_ >> std::noskipws >> currentChar) {
		outFile_ << char(((unsigned char)currentChar) +
			getOffset(input_ == DECRYPT));
	}
}



void Manager::runSubstitution()
{
	std::vector<unsigned char> numbersRemaining;
	std::vector<unsigned char> redirections;

	for (std::size_t i = 0; i < 256; ++i) {
		numbersRemaining.push_back((unsigned char) i);
	}

	while (numbersRemaining.size() > 0) {
		std::size_t remainingIndex = randRange(0, numbersRemaining.size());
		unsigned char newNumber = numbersRemaining[remainingIndex];
		numbersRemaining.erase(numbersRemaining.begin() + remainingIndex);

		redirections.push_back(newNumber);
	}

	char currentChar;
	while (inFile_ >> std::noskipws >> currentChar) {
		unsigned char currentCharIndex = (unsigned char) currentChar;
		char newChar;
		if (input_ == ENCRYPT) {
			newChar = char(redirections.at(currentCharIndex));
		}
		else {
			auto index = std::find(
				redirections.begin(), redirections.end(),
				std::size_t(currentCharIndex));
			if (index != redirections.end()) {
				std::cout << index - redirections.begin();
				newChar = char(index - redirections.begin());
			}
		}
		outFile_ << newChar;
	}



}










