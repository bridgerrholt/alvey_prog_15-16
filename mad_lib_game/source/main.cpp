#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <vector>

#include <chrono>


#include "get_lowered.h"
#include "rand_range.h"

#include "get_stripped_input.h"

#include "file_selector.h"
#include "manager.h"


int main(int argc, char* argv[])
{
	// Seed the RNG with the current time.
	auto currentDuration =
		std::chrono::system_clock::now().time_since_epoch();
	auto currentMilliseconds = std::chrono::duration_cast<
		std::chrono::milliseconds>(currentDuration).count();
	srand(currentMilliseconds);

	// Make the FileSelector linking to "stories".
	FileSelector fileSelector("stories/");

	// If there are inputs, set them to be the input story text files.
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			fileSelector.pushFileName(argv[i]);
		}
	}
	// If no inputs, set to the default files.
	else {
		fileSelector.pushFileName("story_000.txt");
		fileSelector.pushFileName("story_001.txt");
	}

	// File name of the next story to be used.
	std::string nextFileName = fileSelector.getRandomFileName();

	// The main game loop, breaks upon request.
	while (true) {
		// Load a file again every loop.
		Manager manager(nextFileName);

		// Ask the questions and print the story.
		manager.run();


		// Check if the user wants to keep playing.
		std::cout << "Play [A]nother, the [S]ame, or [Q]uit? ";
		std::string questionInput = getLowered(getStrippedInput());

		// If they want the same story, don't change the file.
		if (questionInput == "s" || questionInput == "same") {

		}

		// If they want to quit, break out of the loop.
		else if (questionInput == "q" || questionInput == "quit") {
			break;
		}

		// If they entered invalid text, assume they want another story.
		else {
			// If they did not enter the appropriate text, alert them.
			if (questionInput != "a" && questionInput != "another") {
				std::cout << "Playing another...\n";
			}

			// Tell them when they've completed a cycle.
			if (fileSelector.getRemainingIndexesSize() == 0) {
				std::cout << "Note: you have played them all.\n";
			}

			nextFileName = fileSelector.getRandomFileName();
		}

		// Clear the buffer.
		std::cout << std::endl;
	}

	// Exit.
	return 0;
}