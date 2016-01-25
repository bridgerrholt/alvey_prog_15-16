#include <get_stripped_input.h>

#include "manager.h"

int main(int argc, char* argv[])
{
	Manager manager;

	while (true) {
		manager.run();

		std::string input = getStrippedInput("Play again?", "\n ");
		break;
	}


	return 0;
}