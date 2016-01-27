// A non-object class for handling simple input functions.

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>

class InputHandler
{
public:
	// Simply displays either the default question or the given question.
	static void printQuestion();
	static void printQuestion(
		const std::string& question,
		bool useDefaultEnding = true);
	static void printQuestion(
		const std::string& question,
		const std::string& ending,
		bool useDefaultEnding = false);


	// Before the input is collected, the default question and ending are both
	// displayed unless the passed arguments declare otherwise.

	// Uses cin to get an entire line of input.
	static std::string getRawInput();
	static void getRawInput(std::string& inputString);

	// Displays the question and gets the input.
	static std::string askRaw();
	static std::string askRaw(
		const std::string& question,
		bool useDefaultEnding = true);
	static std::string askRaw(
		const std::string& question,
		const std::string& ending);

	// Removes the front and back whitespace.
	static std::string getStrippedInput();
	static std::string askStripped();
	static std::string askStripped(
		const std::string& question,
		bool useDefaultEnding = true);
	static std::string askStripped(
		const std::string& question,
		const std::string& ending);


	// Setters.
	static void setDefaultQuestion(
		const std::string& defaultQuestion);

	static void setDefaultEnding(
		const std::string& defaultEnding);


private:
	// Private constructor prevents object creation. This class is not meant
	// to have several objects, it's purely static.
	InputHandler() {}

	// Displayed if no question is provided.
	static std::string defaultQuestion_;

	// Displayed after the question unless a different ending is provided or
	// explicitly stated otherwise.
	static std::string defaultEnding_;
};

#endif