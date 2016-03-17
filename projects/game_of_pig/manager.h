// An object that runs one game when asked to.

#ifndef GAME_OF_PIG_MANAGER_H
#define GAME_OF_PIG_MANAGER_H

#include <vector>
#include <input_handler.h>

#include "../explorer/manager.h"

namespace game_of_pig
{

class Manager : public explorer::Manager
{
public:
	// Constructors.
	Manager(const explorer::Manager& baseManager, unsigned int pointsNeeded);

	// Runs a single game.
	void run();

private:
	// Runs a player's turn, returning true only if they've won.
	bool runTurn(std::size_t index);

	// Checks if any value in points_ is greater than 100.
	bool checkWinner(std::size_t& winnerIndex);

	// Return a value in the range [1, 6].
	unsigned int rollDie(unsigned int sides = 6);

	// The input handler is made before the manager's construction.
	//InputHandler& inputHandler_;

	// The number of points a player needs to win.
	unsigned int pointsNeeded_;
	
	// One index for each player.
	std::vector<unsigned int> points_;

};

}

#endif