#include <iostream>

#include <memory>

#include <input_handler.h>

#include "manager.h"
#include "project_selector.h"

using namespace explorer;

int main(int argc, char* argv[])
{
	std::unique_ptr<Manager> currentManager;
	ProjectSelector projectSelector;
	projectSelector.pushProject("Binary Search", "B");
	projectSelector.pushProject("Encryption", "E");
	projectSelector.pushProject("Game of Pig", "G");
	projectSelector.pushProject("Hang Man", "H");
	projectSelector.pushProject("Mad Lib Game", "M");

	InputHandler inputHandler = InputHandler(" ");
	inputHandler.pushDefaultEnding("\n ");

	while (true) {
		std::cout << projectSelector.getFormattedProjects() << '\n';
		inputHandler.printQuestion("Select a project:");

		//currentManager->run();

		break;
	}

	return 0;
}