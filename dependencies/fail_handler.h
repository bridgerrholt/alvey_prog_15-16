// Holds a bool, can output a message and change the bool simutaniously.

#ifndef FAIL_HANDLER_H
#define FAIL_HANDLER_H

#include <string>

class FailHandler
{
public:
	FailHandler();

	// Outputs the given string and sets the error bool to true.
	void error(const std::string& errorString);

	// Sets the error bool back to false.
	void reset();

	// Returns if an error has occured since the last reset().
	bool get();

private:
	// Set true by error() and false by reset().
	bool fail_;
};

#endif