// When created, asks for a range to guess in and runs the process.

#ifndef MANAGER_H
#define MANAGER_H

#include <string>

class Manager
{
public:
	// Asks for the range.
	Manager();

private:
	// The type of number to be used for the range.
	typedef long int Number;

	// Asks if the given number is greater than or less than the
	// target number.
	void makeGuess();

	// Print an error plus a newline, set fail to true.
	void makeError(const std::string& errorString);
	// Sets fail_ to false;
	void resetFail();

	// Sets the difference appropriately.
	void calculateDifference();

	// Tracks if any failures have occured.
	bool fail_;

	// The range.
	Number min_;
	Number max_;
	Number difference_;

	// Incremented every makeGuess called.
	std::size_t guessCount_;

};

#endif