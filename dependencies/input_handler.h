// A class for handling simple input functions.

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>

class InputHandler
{
public:
	InputHandler(const std::string& defaultEnding);

	// Simply displays either the default question or the given question.
	void printQuestion();
	void printQuestion(
		const std::string& question,
		bool useDefaultEnding = true,
		std::size_t defaultEndingIndex = 0);
	void printQuestion(
		const std::string& question,
		const std::string& ending,
		bool useDefaultEnding = false,
		std::size_t defaultEndingIndex = 0);


	// Before the input is collected, the default question and ending are both
	// displayed unless the passed arguments declare otherwise.

	// Uses cin to get an entire line of input.
	std::string getRawInput();
	void getRawInput(std::string& inputString);

	// Displays the question and gets the input.
	std::string askRaw();
	std::string askRaw(
		const std::string& question,
		bool useDefaultEnding = false,
		std::size_t defaultEndingIndex = 0);
	std::string askRaw(
		const std::string& question,
		const std::string& ending);

	// Removes the front and back whitespace.
	std::string getStrippedInput();
	std::string askStripped();
	std::string askStripped(
		const std::string& question,
		bool useDefaultEnding = false,
		std::size_t defaultEndingIndex = 0);
	std::string askStripped(
		const std::string& question,
		const std::string& ending);


	// Setters.
	void setDefaultQuestion(
		const std::string& defaultQuestion);

	void pushDefaultEnding(
		const std::string& defaultEnding);


private:
	// Displayed if no question is provided.
	std::string defaultQuestion_;

	// Displayed after the question unless a different ending is provided or
	// explicitly stated otherwise.
	std::vector<std::string> defaultEndings_;
};

#endif