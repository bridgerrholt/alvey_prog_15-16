#include <cstdlib>
#include <time.h>

#include <get_stripped_input.h>
#include <get_lowered.h>

#include <input_handler.h>

#include "manager.h"

int main(int argc, char* argv[])
{
	// Seeds the RNG with the current timestamp.
	std::srand(time(0));

	// The main input handler, passed to the manager constructor.
	InputHandler inputHandler;

	// Makes questions end in a newline and space.
	inputHandler.setDefaultEnding("\n ");

	// Object that takes control to run a game on command.
	Manager manager(inputHandler, "dictionaries/dictionary.txt", "text_images/man");

	// Play games until the player requests to quit.
	while (true) {
		// Runs a single game,
		// returns once a player reaches the winning score.
		manager.run();

		// Quits if the player requests to.
		std::string input =
			getLowered(inputHandler.askStripped("Play again? (y/n)"));
		if (input == "n")
			break;
	}

	return 0;
}