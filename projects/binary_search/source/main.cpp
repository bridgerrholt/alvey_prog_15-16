// Holds the main function.
// Runs a loop that creates a Manager object (causing one game to run),
// then asks the player if they want to quit.

#include <iostream>
#include <string>

#include <get_stripped_input.h>
#include <get_lowered.h>

#include <input_handler.h>

#include "manager.h"

int main(int argc, char* argv[])
{
	// The object that runs a single game when its "run" method is called.
	Manager manager;

	// The main game loop, quit on prompt.
	while (true) {
		// Handles a whole game of guessing.
		manager.run();

		// If they put 'n', quit.
		std::cout << "\nPlay again? (y/n) ";
		std::string strippedInput = getLowered(getStrippedInput());
		if (strippedInput == "n") {
			break;
		}
		std::cout << std::endl;
	}

	// Exit.
	return 0;
}