// A class with several children, one for each project.

#ifndef EXPLORER_MANAGER_H
#define EXPLORER_MANAGER_H

#include <fail_handler.h>

class InputHandler;

namespace explorer
{

class Manager
{
public:
	Manager(InputHandler& inputHandler);

	virtual void run() {}

protected:
	FailHandler fail_;
	InputHandler& inputHandler_;

};

}

#endif