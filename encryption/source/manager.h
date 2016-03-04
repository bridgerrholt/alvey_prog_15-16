// An object that runs one game when asked to.

#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <input_handler.h>

class Manager
{
public:
	// Constructors.
	Manager(InputHandler& inputHandler);

	// Runs a single game.
	void run();

private:
	enum InputChoice
	{
		ENCRYPT,
		DECRYPT,
		QUIT
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

	void runCaesarian();
	void runPseudoRandom();
	void runSubstitution();

	// The input handler is made before the manager's construction.
	InputHandler& inputHandler_;

	std::string password_;

	InputChoice input_;



};

#endif