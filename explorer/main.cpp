#include <iostream>

#include <memory>
#include <random>
#include <chrono>

#include <input_handler.h>
#include <get_lowered.h>

#include "manager.h"
#include "project_selector.h"
#include "project_identifier.h"
#include "make_manager.h"

using namespace explorer;

int main(int argc, char* argv[])
{
	// Seed the RNG with the current time.
	auto currentDuration =
		std::chrono::system_clock::now().time_since_epoch();
	auto currentMilliseconds = std::chrono::duration_cast<
		std::chrono::milliseconds>(currentDuration).count();
	srand(currentMilliseconds);

	std::unique_ptr<Manager> currentManager;
	ProjectSelector projectSelector;
	projectSelector.pushProject("Binary Search", "B", BINARY_SEARCH);
	projectSelector.pushProject("Encryption",    "E", ENCRYPTION);
	projectSelector.pushProject("Game of Pig",   "G", GAME_OF_PIG);
	projectSelector.pushProject("Hang Man",      "H", HANG_MAN);
	projectSelector.pushProject("Mad Lib Game",  "M", MAD_LIB_GAME);

	InputHandler inputHandler = InputHandler(" ");
	inputHandler.pushDefaultEnding("\n ");

	Manager baseManager = Manager(inputHandler);

	while (true) {
		std::cout << projectSelector.getFormattedProjects() << '\n';
		inputHandler.printQuestion("Select a project:");

		std::string projectSelection;
		ProjectIdentifier projectIdentifier;

		while (true) {
			projectSelection = inputHandler.askStripped("");

			// If valid input, stop asking.
			if (projectSelector.findProject(
				projectSelection, projectIdentifier)) {
				break;
			}
			// Otherwise it's invalid, keep asking.
			else {
				inputHandler.printQuestion("Invalid input");
			}
		}

		std::cout << '\n';

		currentManager = std::unique_ptr<Manager>(
			makeManager(baseManager, projectIdentifier));

		bool toQuit = false;
		while (true) {
			currentManager->run();

			std::string userInput;
			inputHandler.printQuestion("\nPlay the [S]ame, [A]nother, or [Q]uit?");

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