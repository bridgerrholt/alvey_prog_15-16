#include "manager.h"

#include <iostream>
#include <string>
#include <array>

#include <constants.h>
#include <rand_range.h>
#include <get_stripped_input.h>
#include <get_lowered.h>

using namespace encryption;

Manager::Manager(const explorer::Manager& baseManager) :
	explorer::Manager(baseManager)
{

}



void Manager::run()
{
	input_ = askInput();
	if (input_ == QUIT)
		return;
	std::cout << "\n";

	EncryptionMethod method = askMethod();
	std::cout << "\n";
	password_ = askPassword();
	std::cout << "\n";

	std::string fileNameLabel = "input";
	std::string& fileNameVar = inputFileName_;

	for (std::size_t i = 0; i < 2; ++i) {
		std::cout << "Enter " + fileNameLabel + " file name:";

		while (true) {
			fileNameVar =
				inputHandler_.askStripped("", true, std::size_t(1));

			if (fileNameVar == "") {
				std::cout << "Invalid input.";
			}
			else {
				break;
			}

		}

		if (i == 0) {
			fileNameLabel = "ouput";
			fileNameVar = outputFileName_;
		}
	};

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


}



Manager::InputChoice Manager::askInput()
{
	std::cout <<
		"[E]ncrypt\n"
		"[D]ecrypt\n"
		"[Q]uit\n"
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
		else if (input == "q" || input == "quit") {
			return QUIT;
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
		"[S]ubstitution cipher\n"
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

}



void Manager::runPseudoRandom()
{

}



void Manager::runSubstitution()
{

}




