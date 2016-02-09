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
	Manager(InputHandler& inputHandler, const std::string& fileName);

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


	void displayLetters();
	void displayGuesses();


	void loadDictionary();
	void selectWord();

	// Print an error plus a newline, set fail to true.
	void makeError(const std::string& errorString);
	// Sets fail_ to false;
	void resetFail();

	InputHandler& inputHandler_;

	std::string fileName_;

	std::deque<std::string> dictionary_;

	std::string currentWord_;

	std::vector<Letter> letters_;

	std::vector<char> guesses_;

	bool fail_;



};

#endif