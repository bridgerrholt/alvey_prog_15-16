// Loads and parses the story file in the constructor.
// Asks the questions and then prints the completed story.

#ifndef MAD_LIB_MANAGER_H
#define MAD_LIB_MANAGER_H

#include <string>
#include <vector>

#include "../explorer/manager.h"
#include "file_selector.h"

namespace mad_lib
{

class Manager : public explorer::Manager
{
public:
	// Loads and parses the file.
	Manager(explorer::Manager baseManager,
		const std::string& pathName);

	// Asks the questions and prints the story.
	void run();

private:
	// A simple set of strings describing the objects in the file.
	class InputObject {
	public:
		// Must be initialized with a label.
		InputObject(std::string labelSet) :
			label(labelSet), content("") { }

		// The type of object (noun, adjective, etc.).
		std::string label;
		// The inputted text.
		std::string content;
	};

	void reset();

	// Turns all the text into a list of strings,
	// in between each string is an input object.
	void pullFile();

	FileSelector fileSelector_;

	// The actual text of the story.
	std::vector<std::string> storyTexts_;

	// The labels and content of the objects to be inputted.
	std::vector<InputObject> inputObjects_;

	bool alreadyPlayed_;

};

}

#endif