// An object that runs one game when asked to.

#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <deque>
#include <vector>

#include <input_handler.h>

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

	void displayImage();
	void displayLetters();
	void displayRevealedLetters();
	void displayGuesses();


	void loadDictionary();
	void selectWord();

	void loadImages();

	// Print an error plus a newline, set fail to true.
	void makeError(const std::string& errorString);
	// Sets fail_ to false;
	void resetFail();

	InputHandler& inputHandler_;

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
	std::size_t lives_;
	std::size_t livesLeft_;


	// Path for the file of text images.
	std::string imagesFileName_;

	// Displayed depending on amount of incorrect guesses.
	std::vector<std::string> images_;


	// A fail flag for errors.
	bool fail_;



};

#endif