#include <iostream>
#include <exception>
#include <vector>
#include <queue>

#include <get_stripped_input.h>
#include <is_unsigned_integer.h>
#include <rand_range.h>
#include <get_lowered.h>

#include "manager.h"

int main(int argc, char* argv[])
{
	// The main game loop, quit on prompt.
	while (true) {
		// The manager constructor handles a whole game of guessing.
		Manager manager;

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