// This class itself has no actual use, however each of its children are
// used to excecute a project.

#ifndef EXPLORER_MANAGER_H
#define EXPLORER_MANAGER_H

#include <fail_handler.h>

class InputHandler;

namespace explorer
{

class Manager
{
public:
  // There should be one InputHandler across all project managers.
  Manager(InputHandler& inputHandler);

  // For children, runs the body of their specific projects.
  virtual void run() {}

protected:
  FailHandler fail_;
  InputHandler& inputHandler_;

};

}

#endif