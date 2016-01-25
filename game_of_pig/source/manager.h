// An object that runs one game when asked to.

#ifndef MANAGER_H
#define MANAGER_H

#include <vector>

class Manager
{
public:
	// Constructors.
	Manager();

	// Runs a single game.
	void run();

private:
	// Runs a player's turn, returning true only if they've won.
	bool runTurn(std::size_t index);

	// Checks if any value in points_ is greater than 100.
	bool checkWinner(std::size_t& winnerIndex);

	// Return a value in the range [1, 6].
	unsigned int rollDie(unsigned int sides = 6);

	// One index for each player.
	std::vector<unsigned int> points_;

	// The number of points a player needs to win.
	unsigned int pointsNeeded_;

};

#endif