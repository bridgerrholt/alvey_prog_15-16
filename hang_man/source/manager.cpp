#include "manager.h"

#include <stdio.h>
#include <ctype.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <exception>
#include <stdexcept>

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

		healthMax_(6),
		livesMax_(3),
		computerLivesMax_(3)
{
	loadDictionary();
	loadImages();
}



void Manager::run()
{
	lives_ = livesMax_;
	computerLives_ = computerLivesMax_;

	while (lives_ >= 1 && computerLives_ >= 1) {
		health_ = healthMax_;
		guesses_ = std::vector<char>();

		displayLives("You have", lives_);
		displayLives("The computer has", computerLives_);
		selectWord();

		// Play until the player wins or loses.
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
			--computerLives_;
		}
		else {
			std::cout << "You lose!\n";
			std::cout << "The correct answer is " <<
				ColorCodes::doB(currentWord_) << "!\n";
			--lives_;
		}

		std::cout << std::endl;
	}

	// If the player lost.
	if (lives_ == 0) {
		std::cout << ColorCodes::doB("GAME OVER") << "\n";
	}

	// If the computer lost.
	else {
		std::cout << "You beat the computer!\n";
	}

}



void Manager::runGuess()
{
	displayImage();
	displayLetters();
	displayGuesses();

	// Ask for the guess.
	std::cout << "\n";
	std::string input =
		getLowered(inputHandler_.askStripped("Guess:"));
	char inputChar = input[0];

	// Keep asking until they provide a single letter.
	while (true) {
		fail_.reset();

		if (input.size() != 1) {
			fail_.error("Must be 1 letter.");
		}
		else if (!isalpha(inputChar)) {
			fail_.error("Must be a letter.");
		}
		else {
			// Error if it was already guessed.
			bool alreadyGuessed = false;

			// Search in the incorrect guesses.
			for (auto i = guesses_.begin(); i != guesses_.end(); ++i) {
				if (inputChar == *i) {
					alreadyGuessed = true;
					break;
				}
			}

			// Search in the correct guesses.
			for (auto i = letters_.begin();
				i != letters_.end() && !alreadyGuessed; ++i) {
				if (inputChar == i->content && i->guessed) {
					alreadyGuessed = true;
					break;
				}
			}

			if (alreadyGuessed) {
				fail_.error("Already guessed.");
			}
		}

		if (fail_.get()) {
			input = getLowered(inputHandler_.askStripped(""));
			inputChar = input[0];
		}
		else
			break;
	}

	// Look through the letters to find the guessed letter.
	bool guessedRight = false;
	for (auto i = letters_.begin(); i != letters_.end(); ++i) {
		if (inputChar == i->content) {
			guessedRight = true;
			i->guessed = true;
		}
	}

	// If not found, the guess was incorrect.
	if (!guessedRight) {
		--health_;
		guesses_.push_back(inputChar);
	}

	std::cout << '\n';

}



bool Manager::checkOver(bool& playerWon)
{
	// If they have guessed away all their lives, the computer wins.
	if (health_ == 0) {
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
	// Print every Letter instance for the current word,
	// with a space in between each.
	auto lastLetter = letters_.end()-1;
	for (auto i = letters_.begin(); i != letters_.end(); ++i) {
		std::cout << i->getChar() << " ";

		if (i != lastLetter)
			std::cout << " ";
	}

	std::cout << '\n';
}



void Manager::displayRevealedLetters()
{
	// Print every Letter instance for the current word,
	// with a space in between each and bolding the ones not guessed.
	auto lastLetter = letters_.end()-1;
	for (auto i = letters_.begin(); i != letters_.end(); ++i) {
		// If guessed, display normally.
		if (i->guessed) {
			std::cout << i->content;
		}

		// If not guessed, display bolded.
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
	// Only display something if they have at least 1 incorrect guess.
	// Displays like: [ r, a, n, d, o, m ]
	if (guesses_.size() > 0) {
		std::cout << "[ ";

		auto lastGuess = guesses_.end()-1;
		for (auto i = guesses_.begin(); i != lastGuess; ++i) {
			std::cout << *i << ", ";
		}

		std::cout << *lastGuess << " ]\n";
	}
}



void Manager::displayLives(const std::string& start, std::size_t lives)
{
	/*std::cout << "You have " <<
		ColorCodes::doB(lives_) << " lives left.\n";

	std::cout << "The computer has " <<
		ColorCodes::doB(computerLives_) << " lives left.\n";*/


	std::string livesWord = "lives";
	if (lives == 1)
		livesWord = "life";

	std::cout << start << " " << ColorCodes::doB(lives) <<
		" " << livesWord << " left.\n";
}



void Manager::loadDictionary()
{
	// Simply loads the file and saves each line.
	std::ifstream fileStream(dictionaryFileName_);
	std::string word;

	while (std::getline(fileStream, word)) {
		dictionary_.push_back(word);
	}
}



void Manager::selectWord()
{
	// If all the words have been used, reload the dictionary.
	if (dictionary_.size() <= 0) {
		loadDictionary();
	}

	// Select a random index.
	std::size_t index = randRange(dictionary_.size());
	// Set it as the current word.
	currentWord_ = dictionary_[index];
	// Remove it from the list.
	dictionary_.erase(dictionary_.begin()+index);

	// Clear the collection of Letter instances.
	letters_ = std::vector<Letter>();

	// Add each letter.
	for (auto i = currentWord_.begin(); i != currentWord_.end(); ++i) {
		letters_.push_back(Letter(*i));
	}
}



void Manager::loadImages()
{
	// Load the file.
	std::ifstream fileStream(imagesFileName_);
	// Current line.
	std::string line;
	// Current image represented as rows.
	std::vector<std::string> imageLines;
	// Current image, ready to be printed.
	std::string image;
	// Background for the images.
	std::vector<std::string> gallows;


	// The first line must specify the size of each image.
	std::getline(fileStream, line);

	// Image height in lines.
	std::size_t imageHeight;
	try {
		imageHeight = patch::stoi(line);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}


	// First get the gallows (the background for every image,
	// and the starting image).
	bool gettingGallows = true;

	// Turn all the images into strings and push them.
	do {
		// Concat the amount of rows specified as the height.
		imageLines = std::vector<std::string>();
		image = "";

		// Push the amount of rows specified as the image height.
		for (std::size_t i = 0; i < imageHeight; ++i) {
			// Fail if there isn't another row.
			// Note: Bug where this it fails unless there is
			// an empty row after the last image.
			if (!std::getline(fileStream, line)) {
				throw std::runtime_error("Not enough rows in image");
			}

			imageLines.push_back(line);
		}

		// If it's the first image, copy it as the background.
		if (gettingGallows) {
			gallows = imageLines;
			gettingGallows = false;
		}

		// If the background has been made, put it under the image.
		else {
			// Replace spaces with the gallows background.
			// Loop through the background rows.
			for (std::size_t i = 0; i < gallows.size(); ++i) {

				// If the image is too short, push a row.
				if (i >= imageLines.size()) {
					imageLines.push_back("");
				}

				// Loop through this row of the background and the image.
				for (std::size_t j = 0; j < gallows[i].size(); ++j) {
					// If the image is too thin, concat the background.
					if (j >= imageLines[i].size()) {
						imageLines[i] += gallows[i][j];
					}

					// Replace spaces.
					else if (imageLines[i][j] == ' ') {
						imageLines[i][j] = gallows[i][j];
					}

				}
			}
		}

		// Concat the rows, with new lines in between.
		for (auto i = imageLines.begin(); i != imageLines.end(); ++i) {
			image += *i;

			// Have a new line between each row, but not after the last row.
			if (i != imageLines.end()-1) {
				image += "\n";
			}
		}

		// Push the new image.
		images_.push_back(image);


	// Ignore the lines in between images.
	} while (std::getline(fileStream, line));
}




