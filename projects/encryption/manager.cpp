#include "manager.h"

#include <iostream>
#include <string>
#include <array>

#include <constants.h>
#include <rand_range.h>
#include <get_stripped_input.h>
#include <get_lowered.h>

#include <functional>

using namespace encryption;

Manager::Manager(const explorer::Manager& baseManager) :
	explorer::Manager(baseManager),
	alphabet_("abcdefghijklmnopqrstuvwxyz"
			 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			 "0123456789"
			 ",.?! \t\n\r")
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
		inFile_ = std::ifstream(inputFileName_);
		outFile_ = std::ofstream(outputFileName_);
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



void Manager::runCaesarian()
{
	int offset = randRange(1, alphabet_.size());
	if (input_ == DECRYPT)
		offset = -offset;
	std::cout << "Using the offset of " << offset << '\n';

	char currectChar;
	while (inFile_ >> std::noskipws >> currectChar) {
		std::string a = std::string(1, currectChar);
		std::size_t charIndex =
			alphabet_.find_first_of(a);
			std::cout << a << '\n';

		std::cout << (charIndex == std::string::npos) << '\n';

		if (charIndex != std::string::npos) {
			int newIndex = int(charIndex)+offset;
			if (newIndex >= alphabet_.size())
				newIndex -= alphabet_.size();
			else if (newIndex < 0)
				newIndex += alphabet_.size();

			std::cout << " " << newIndex << '\n';

			outFile_ << alphabet_.at(newIndex);
			std::cout << alphabet_.at(newIndex);
		}
	}
}



void Manager::runPseudoRandom()
{

}



void Manager::runSubstitution()
{

}




