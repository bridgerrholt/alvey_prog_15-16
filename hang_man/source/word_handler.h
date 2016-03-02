// A word is a list of these special character handlers.

#ifndef HANG_MAN_WORD_HANDLER_H
#define HANG_MAN_WORD_HANDLER_H

#include <string>

#include <vector>

class WordHandler
{
public:

private:
	// A word is a list of these special character handlers.
	class Letter
	{
		Letter(char contentSet);

		std::string getChar();

		bool guessed;
		char content;
	};

	typedef std::vector<Letter> LetterList;
	typedef std::vector<LetterList::iterator> LetterReferenceList;
	
	LetterList guesses_;
	LetterReferenceList correctGuesses_;
	LetterReferenceList incorrectGuesses_;
};

#endif