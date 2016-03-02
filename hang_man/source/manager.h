// An object that runs one game when asked to.

#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <deque>
#include <vector>

#include <input_handler.h>
#include <fail_handler.h>

class Manager
{
public:
	// Constructors.
	Manager(InputHandler& inputHandler,
		const std::string& dictionaryFileName,
		const std::string& imagesFileName);

	// Runs a single game.
	void run();

private:
	// A word is a list of these special character handlers.
	class Letter
	{
	public:
		Letter(char contentSet);

		std::string getChar();

		bool guessed;
		char content;
	};

	void runGuess();
	bool checkOver(bool& playerWon);

	// Prints the specific image string based on the lives left.
	void displayImage();
	// Prints a letter for a guessed letter,
	// and an underscore for every other letter.
	void displayLetters();
	// Prints a letter for a guessed letter,
	// and a bold letter for every other letter.
	void displayRevealedLetters();
	// Prints the list of guesses, surrounded in brackets.
	void displayGuesses();
	// Prints your lives and the computer's lives.
	void displayLives(const std::string& name, std::size_t lives);

	// Makes a list of all the words in the given file.
	void loadDictionary();
	// Randomly selects a word from the list, removing it as well.
	void selectWord();

	// Reads the text file, capturing the several "images".
	void loadImages();


	InputHandler& inputHandler_;
	FailHandler fail_;

	// Path for the file of words.
	std::string dictionaryFileName_;

	// List of words from the file.
	std::deque<std::string> dictionary_;

	// Word currently being guessed.
	std::string currentWord_;

	// All the letters in the current word.
	std::vector<Letter> letters_;

	// All the letters guessed so far for the current word.
	std::vector<char> guesses_;

	// Amount of guesses before they lose.
	std::size_t healthMax_;
	std::size_t health_;

	// Amount of lives before game over.
	std::size_t livesMax_;
	std::size_t lives_;

	std::size_t computerLivesMax_;
	std::size_t computerLives_;


	// Path for the file of text images.
	std::string imagesFileName_;

	// Displayed depending on amount of incorrect guesses.
	std::vector<std::string> images_;
};

#endif