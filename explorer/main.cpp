#include <iostream>

#include <memory>

#include <input_handler.h>
#include <get_lowered.h>

#include "manager.h"
#include "project_selector.h"

#include "binary_search/manager.h"
#include "encryption/manager.h"
#include "game_of_pig/manager.h"
#include "hang_man/manager.h"
#include "mad_lib_game/manager.h"

using namespace explorer;

int main(int argc, char* argv[])
{
	std::unique_ptr<Manager> currentManager;
	ProjectSelector projectSelector;
	projectSelector.pushProject("Binary Search", "B");
	projectSelector.pushProject("Encryption",    "E");
	projectSelector.pushProject("Game of Pig",   "G");
	projectSelector.pushProject("Hang Man",      "H");
	projectSelector.pushProject("Mad Lib Game",  "M");

	InputHandler inputHandler = InputHandler(" ");
	inputHandler.pushDefaultEnding("\n ");

	Manager baseManager = Manager(inputHandler);

	while (true) {
		std::cout << projectSelector.getFormattedProjects() << '\n';
		inputHandler.printQuestion("Select a project:");

		std::string projectSelection;
		std::size_t projectIndex;

		do {
			projectSelection = inputHandler.askStripped("");

		} while (!projectSelector.findProject(
			projectSelection, projectIndex));

		switch (projectIndex) {
		case 0:
			currentManager = std::unique_ptr<Manager>(
				new binary_search::Manager(baseManager));
			break;
		case 1:
			currentManager = std::unique_ptr<Manager>(
				new encryption::Manager(baseManager));
			break;
		case 2:
			currentManager = std::unique_ptr<Manager>(
				new game_of_pig::Manager(baseManager, 100));
			break;
		case 3:
			currentManager = std::unique_ptr<Manager>(
				new hang_man::Manager(baseManager,
				"../../dictionaries/american-english-no-accents.txt",
				"text_images/man.txt"));
			break;
		/*case 4:
			currentManager = std::unique_ptr<Manager>(new mad_lib::Manager(baseManager, const std::string& fileName));
			break;*/
		default:
			return 0;
		}

		bool toQuit = false;
		while (true) {
			currentManager->run();

			std::string userInput;
			inputHandler.printQuestion("\nPlay the [S]ame, Play [A]nother, [Q]uit:");

			bool toPlayAnother = false;

			while (true) {
				userInput = getLowered(inputHandler.askStripped(""));

				if (userInput == "s") {
					break;
				}
				else if (userInput == "a") {
					toPlayAnother = true;
					break;
				}
				else if (userInput == "q") {
					toQuit = true;
					break;
				}
				else {
					inputHandler.printQuestion("Invalid input");
				}
			}

			std::cout << "\n";

			if (toPlayAnother || toQuit)
				break;
		}

		if (toQuit)
			break;
	}

	return 0;
}