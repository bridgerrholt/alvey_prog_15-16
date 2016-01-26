// A non-object class for handling simple input functions.

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>

class InputHandler
{
public:
	static std::string getRawInput();
	static std::string getRawInput(
		const std::string& question,
		bool useDefaultEnding);
	static std::string getRawInput(
		const std::string& question,
		const std::string& ending = "",
		bool useDefaultEnding = true);

	static std::string getStrippedInput();
	static std::string getStrippedInput(
		const std::string& question,
		bool useDefaultEnding);
	static std::string getStrippedInput(
		const std::string& question,
		const std::string& ending = "",
		bool useDefaultEnding = true);

	static void setDefaultQuestion(
		const std::string& defaultQuestion);

	static void setDefaultEnding(
		const std::string& defaultEnding);

	static void askQuestion(
		const std::string& question,
		const std::string& ending = "",
		bool useDefaultEnding = true);

private:
	static std::string defaultQuestion_;
	static std::string defaultEnding_;

};

#endif