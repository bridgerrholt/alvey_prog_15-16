#include "manager.h"
#include "get_stripped_input.h"

#include "constants.h"

#include <exception>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

extern const ColorCodes G_COLOR_CODES;

Manager::Manager(std::string fileName)
{
	// Text in between splits.
	std::string currentString = "";

	// Load and parse the file.
	// Note: not true "parsing"
	try {
		// Load the file.
		std::ifstream file(fileName);

		if (!file.good()) {
			throw std::exception();
		}

		// Loop through the entire file.
		char i;
		while (true) {
			// Advance.
			file.get(i);

			// Break if it's past the last character.
			if (file.eof())
				break;

			// If it's the start of an input object,
			// add the current slice to the storyTexts_ container.
			if (i == '<') {
				storyTexts_.push_back(currentString);
				currentString = "";
			}

			// If it's the end of an input object,
			// add the current slice to the inputObjects_ container.
			else if (i == '>') {
				inputObjects_.push_back(InputObject(currentString));
				currentString = "";
			}

			// Otherwise, simply add this character.
			else {
				currentString += i;
			}
		}
	}

	// If the file failed to open or to be read.
	catch (std::exception& exception) {
		std::cout << "Exception opening/reading file (" << fileName << ").";
	}

	// Add whatever more there is.
	// Note: run() depends on there being storyTexts_'s size being 1 greater
	//       than inputObjects_'s size, so add even if it's an empty string.
	storyTexts_.push_back(currentString);
}



void Manager::run()
{
	// Get the input for all the objects.
	for (auto i = inputObjects_.begin(); i != inputObjects_.end(); ++i) {
		std::cout << i->label << ": ";
		i->content = getStrippedInput();
	}

	// Print the completed story.
	std::cout << "\n";
	for (std::size_t i = 0; i < storyTexts_.size()-1; ++i) {
		// [story text][underline][input object][reset]
		std::cout << storyTexts_[i] <<
			constants::G_COLOR_CODES.underline << inputObjects_[i].content <<
			constants::G_COLOR_CODES.reset;
	}
	std::cout << storyTexts_[storyTexts_.size()-1] << '\n';
	std::cout << std::endl;
}