// An object that runs one game when asked to.

#ifndef ENCRYPTION_MANAGER_H
#define ENCRYPTION_MANAGER_H

#include <vector>
#include <fstream>

#include <input_handler.h>

#include "../explorer/manager.h"

namespace encryption
{

class Manager : public explorer::Manager
{
public:
	// Constructors.
	Manager(const explorer::Manager& baseManager);

	// Runs a single game.
	void run();

private:
	enum InputChoice
	{
		ENCRYPT,
		DECRYPT
	};

	enum EncryptionMethod
	{
		CAESARIAN,
		PSEUDO_RANDOM,
		SUBSTITUTION
	};

	InputChoice askInput();
	EncryptionMethod askMethod();
	std::string askPassword();

	int getOffset(bool isDecrypting);

	void runCaesarian();
	void runPseudoRandom();
	void runSubstitution();

	// The input handler is made before the manager's construction.
	//InputHandler& inputHandler_;

	std::string password_;

	InputChoice input_;

	std::string inputFileName_;
	std::string outputFileName_;

	std::ifstream inFile_;
	std::ofstream outFile_;


};

}

#endif