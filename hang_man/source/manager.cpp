#include "manager.h"

#include <stdio.h>
#include <ctype.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <exception>

#include <patch/stoi.h>

#include <constants.h>
#include <rand_range.h>
#include <get_stripped_input.h>
#include <get_lowered.h>

Manager::Letter::Letter(char contentSet) :
	content(contentSet),
	guessed(false)
{

}



std::string Manager::Letter::getChar()
{
	if (guessed)
		return std::string(1, content);
	else
		return "_";
}



Manager::Manager(
	InputHandler& inputHandler,
	const std::string& dictionaryFileName,
	const std::string& imagesFileName) :
		inputHandler_(inputHandler),
		dictionaryFileName_(dictionaryFileName),
		imagesFileName_(imagesFileName),

		lives_(6),
		fail_(false)
{
	loadDictionary();
	loadImages();
}



void Manager::run()
{
	livesLeft_ = lives_;
	guesses_ = std::vector<char>();

	selectWord();


	bool playerWon;
	while (!checkOver(playerWon)) {
		runGuess();
	}

	displayImage();
	displayRevealedLetters();
	displayGuesses();

	if (playerWon) {
		std::cout << "You win!\n";
		std::cout << "You guessed " <<
			ColorCodes::doB(currentWord_) << "!\n";
	}
	else {
		std::cout << "You lose!\n";
		std::cout << "The correct answer is " <<
			ColorCodes::doB(currentWord_) << "!\n";
	}

	std::cout << std::endl;

}



void Manager::runGuess()
{
	displayImage();
	displayLetters();
	displayGuesses();

	std::cout << "\n";
	std::string input =
		getLowered(inputHandler_.askStripped("Guess:"));
	char inputChar = input[0];

	while (true) {
		resetFail();

		if (input.size() != 1) {
			makeError("Must be 1 letter.");
		}
		else if (!isalpha(inputChar)) {
			makeError("Must be a letter.");
		}
		else {
			// Error if it was already guessed.
			bool alreadyGuessed = false;

			for (auto i = guesses_.begin(); i != guesses_.end(); ++i) {
				if (inputChar == *i) {
					alreadyGuessed = true;
					break;
				}
			}

			for (auto i = letters_.begin();
				i != letters_.end() && !alreadyGuessed; ++i) {
				if (inputChar == i->content && i->guessed) {
					alreadyGuessed = true;
					break;
				}
			}

			if (alreadyGuessed) {
				makeError("Already guessed.");
			}
		}

		if (fail_) {
			input = getLowered(inputHandler_.askStripped(""));
			inputChar = input[0];
		}
		else
			break;
	}

	bool guessedRight = false;
	for (auto i = letters_.begin(); i != letters_.end(); ++i) {
		if (inputChar == i->content) {
			guessedRight = true;
			i->guessed = true;
		}
	}

	if (!guessedRight) {
		--livesLeft_;
		guesses_.push_back(inputChar);
	}

	std::cout << '\n';

}



bool Manager::checkOver(bool& playerWon)
{
	// If they have guessed away all their lives, the computer wins.
	if (livesLeft_ == 0) {
		playerWon = false;
		return true;
	}

	// If they have guessed all the letters, they win.
	// Check if any letter is not guessed.
	bool allGuessed = true;
	for (auto i = letters_.begin(); i != letters_.end(); ++i) {
		// If it is not guessed, they'll keep playing.
		if (!i->guessed) {
			allGuessed = false;
			break;
		}
	}

	if (allGuessed) {
		playerWon = true;
		return true;
	}
	
	return false;
}



void Manager::displayImage()
{
	std::cout << images_.at(guesses_.size());
	std::cout << '\n';
}



void Manager::displayLetters()
{
	auto lastLetter = letters_.end()-1;
	for (auto i = letters_.begin(); i != lastLetter; ++i) {
		std::cout << i->getChar() << " ";
	}

	std::cout << lastLetter->getChar() << "\n";
}



void Manager::displayRevealedLetters()
{
	auto lastLetter = letters_.end()-1;
	for (auto i = letters_.begin(); i != letters_.end(); ++i) {
		if (i->guessed) {
			std::cout << i->content;
		}
		else {
			std::cout << ColorCodes::bold << i->content <<
				ColorCodes::reset;
		}

		if (i != lastLetter)
			std::cout << " ";
	}

	std::cout << '\n';
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
	std::ifstream fileStream(dictionaryFileName_);
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

	std::size_t index = randRange(dictionary_.size());
	currentWord_ = dictionary_[index];
	dictionary_.erase(dictionary_.begin()+index);

	letters_ = std::vector<Letter>();

	for (auto i = currentWord_.begin(); i != currentWord_.end(); ++i) {
		letters_.push_back(Letter(*i));
	}
}



void Manager::loadImages()
{
	std::ifstream fileStream(imagesFileName_);
	std::string line;
	std::string image;

	std::getline(fileStream, line);

	std::size_t imageHeight;
	try {
		imageHeight = patch::stoi(line);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}

	do {
		image = "";
		for (std::size_t i = 0; i < imageHeight; ++i) {
			std::getline(fileStream, line);
			image += line;

			if (i != imageHeight-1) {
				image += "\n";
			}
		}

		images_.push_back(image);

	} while (std::getline(fileStream, line));
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





