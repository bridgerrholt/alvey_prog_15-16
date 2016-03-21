#include <exception>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <get_stripped_input.h>
#include <input_handler.h>
#include <get_lowered.h>
#include <constants.h>

#include "manager.h"

using namespace mad_lib;

Manager::Manager(explorer::Manager baseManager,
	const std::string& pathName) :

	explorer::Manager(baseManager)
{
	alreadyPlayed_ = false;

	fileSelector_ = FileSelector(pathName);
	std::string fileNameRoot = "story_";
	std::string fileNameExtension = ".txt";
	fileSelector_.pushFileName(fileNameRoot + "000" + fileNameExtension);
	fileSelector_.pushFileName(fileNameRoot + "001" + fileNameExtension);
}



void Manager::run()
{
	bool toPlayAnother = true;

	if (alreadyPlayed_) {
		inputHandler_.printQuestion("Run the [S]ame story or [A]nother story?");
		
		std::string userInput;
		while (true) {
			userInput = getLowered(inputHandler_.askStripped(""));

			if (userInput == "s") {
				toPlayAnother = false;
				break;
			}
			else if (userInput == "a") {
				break;
			}
			else {
				inputHandler_.printQuestion("Invalid input");
			}

		}
	}
	else
		alreadyPlayed_ = true;

	if (toPlayAnother)
		pullFile();
	

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
			ColorCodes::doU(inputObjects_[i].content);
	}
	std::cout << storyTexts_[storyTexts_.size()-1] << '\n';
	std::cout << std::endl;
}



void Manager::reset()
{
	storyTexts_ = std::vector<std::string>();
	inputObjects_ = std::vector<InputObject>();
}



void Manager::pullFile()
{
	reset();

	// File name of the next story to be used.
	std::string nextFileName = fileSelector_.getRandomFileName();

	// Text in between splits.
	std::string currentString = "";

	// Load and parse the file.
	// Note: not true "parsing".
	try {
		// Load the file.
		std::ifstream file(nextFileName);

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
		std::cout <<
		"Exception opening/reading file (" << nextFileName << ").\n";
	}


	// Add whatever more there is.
	// Note: run() depends on there being storyTexts_'s size being 1 greater
	//       than inputObjects_'s size, so add even if it's an empty string.
	storyTexts_.push_back(currentString);
}




