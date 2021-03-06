#include "manager.h"

#include <iostream>
#include <string>

#include <constants.h>
#include <rand_range.h>
#include <get_stripped_input.h>
#include <get_lowered.h>

using namespace game_of_pig;

Manager::Manager(const explorer::Manager& baseManager, unsigned int pointsNeeded) :
	explorer::Manager(baseManager)
{
	pointsNeeded_ = pointsNeeded;
}



void Manager::run()
{
	// May be customizable.
	std::size_t playerCount = 2;

	// Players are only represented by their points.
	for (std::size_t i = 0; i < playerCount; ++i) {
		points_.push_back(0);
	}

	// Set to false when the game is complete.
	bool playing = true;

	// Sets to the index in points_ of the winner.
	std::size_t winnerIndex;

	while (playing) {
		// Run the a turn for all the players.
		for (std::size_t i = 0; i < points_.size(); ++i) {
			//getStrippedInput(
			inputHandler_.askStripped(
				"Player " + ColorCodes::doB(i+1) + ", press return.", false);
			// If they won this turn, set them as the winner
			// and exit the game.
			if (runTurn(i)) {
				winnerIndex = i;
				playing = false;
				break;
			}
		}
	}

	std::cout << ColorCodes::doB("Player " +
		patch::to_string(winnerIndex+1) + " wins!") <<
			"\n" << std::endl;

}



bool Manager::runTurn(std::size_t index)
{
	unsigned int pointsMade = 0;
	bool playing = true;
	bool lostPoints = false;

	while (playing) {
		unsigned int side = rollDie();
		std::cout << "You rolled a " << ColorCodes::doB(side) << "!\n";

		if (side == 1) {
			lostPoints = true;
			pointsMade = 0;
			break;
		}
		else {
			pointsMade += side;

			unsigned int pointsTotal = points_[index]+pointsMade;

			if (pointsTotal >= pointsNeeded_) {
				std::cout << "You made " <<
					ColorCodes::doB(pointsMade) <<
					" points this round, " <<
					ColorCodes::doB("you win!") << "\n\n";
				playing = false;
				break;
			}

			/*std::cout << "You have now made " <<
				ColorCodes::doB(pointsMade) <<
				" points this round, roll again? (y/n)\n ";*/
			std::string input = getLowered(
				inputHandler_.askStripped(
				"You have now made " +
				ColorCodes::doB(pointsMade) +
				" points this round, roll again? (y/n)", std::string(" ")));

			while (true) {
				if (input == "y") {
					break;
				}
				else if (input == "n") {
					playing = false;
					break;
				}
				input = getLowered(
					inputHandler_.askStripped("Enter y or n:"));
			}
		}

	}

	points_[index] += pointsMade;

	if (points_[index] >= pointsNeeded_) {
		return true;
	}


	/*if (lostPoints) {
		std::cout << "You would have made ";
	}
	else {
		std::cout << "You made ";
	}

	std::cout << ColorCodes::doB(pointsMade) <<
		" points this round, your total is " <<
		ColorCodes::doB(points_[index]) << "!\n\n";*/

	std::cout << "Your total is " <<
		ColorCodes::doB(points_[index]) << "!\n\n";


	return false;

}



unsigned int Manager::rollDie(unsigned int sides)
{
	return randRange(1, sides+1);
}












