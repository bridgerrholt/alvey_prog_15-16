// A class for handling simple input functions.

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>

class InputHandler
{
public:
	InputHandler();

	// Simply displays either the default question or the given question.
	void printQuestion();
	void printQuestion(
		const std::string& question,
		bool useDefaultEnding = true);
	void printQuestion(
		const std::string& question,
		const std::string& ending,
		bool useDefaultEnding = false);


	// Before the input is collected, the default question and ending are both
	// displayed unless the passed arguments declare otherwise.

	// Uses cin to get an entire line of input.
	std::string getRawInput();
	void getRawInput(std::string& inputString);

	// Displays the question and gets the input.
	std::string askRaw();
	std::string askRaw(
		const std::string& question,
		bool useDefaultEnding = true);
	std::string askRaw(
		const std::string& question,
		const std::string& ending);

	// Removes the front and back whitespace.
	std::string getStrippedInput();
	std::string askStripped();
	std::string askStripped(
		const std::string& question,
		bool useDefaultEnding = true);
	std::string askStripped(
		const std::string& question,
		const std::string& ending);


	// Setters.
	void setDefaultQuestion(
		const std::string& defaultQuestion);

	void setDefaultEnding(
		const std::string& defaultEnding);


private:
	// Displayed if no question is provided.
	std::string defaultQuestion_;

	// Displayed after the question unless a different ending is provided or
	// explicitly stated otherwise.
	std::string defaultEnding_;
};

#endif