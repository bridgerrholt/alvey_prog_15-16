#include "manager.h"

#include <stdio.h>
#include <ctype.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <constants.h>
#include <rand_range.h>
#include <get_stripped_input.h>
#include <get_lowered.h>

extern const ColorCodes constants::G_COLOR_CODES;

using namespace constants;

Manager::Letter::Letter(char contentSet) :
	guessed(false), content(contentSet)
{

}



std::string Manager::Letter::getChar()
{
	if (guessed)
		return std::string(1, content);
	else
		return "_";
}



Manager::Manager(InputHandler& inputHandler, const std::string& fileName) :
	inputHandler_(inputHandler), fileName_(fileName), fail_(false)
{
	loadDictionary();
	selectWord();
}



void Manager::run()
{
	displayLetters();
	displayGuesses();

	std::cout << "\n";
	std::string input =
		getLowered(inputHandler_.askStripped("Guess:"));

	while (true) {
		resetFail();

		if (input.size() != 1) {
			makeError("Must be 1 letter.");
		}
		else if (!isalpha(input[0])) {
			makeError("Must be a letter.");
		}

		if (fail_)
			input = getLowered(inputHandler_.askStripped(""));
		else
			break;
	}

}



void Manager::displayLetters()
{
	auto lastLetter = letters_.end()-1;
	for (auto i = letters_.begin(); i != lastLetter; ++i) {
		std::cout << i->getChar() << " ";
	}

	std::cout << lastLetter->getChar() << "\n";
}



void Manager::displayGuesses()
{
	if (guesses_.size() > 0) {
		std::cout << "[ ";

		auto lastGuess = guesses_.end()-1;
		for (auto i = guesses_.begin(); i != lastGuess; ++i) {
			std::cout << *i << ", ";
		}

		std::cout << *lastGuess << " ]\n";
	}
}



void Manager::loadDictionary()
{
	std::ifstream fileStream(fileName_);
	std::string word;

	while (std::getline(fileStream, word)) {
		dictionary_.push_back(word);
	}
}



void Manager::selectWord()
{
	if (dictionary_.size() <= 0) {
		loadDictionary();
	}

	std::size_t index = randRange(0, dictionary_.size());
	currentWord_ = dictionary_[index];
	dictionary_.erase(dictionary_.begin()+index);

	for (auto i = currentWord_.begin(); i != currentWord_.end(); ++i) {
		letters_.push_back(Letter(*i));
	}
}



void Manager::makeError(const std::string& errorString)
{
	std::cout << errorString;
	fail_ = true;
}



void Manager::resetFail()
{
	fail_ = false;
}





