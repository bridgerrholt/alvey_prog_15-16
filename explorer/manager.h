/// Base class for all project managers.
/**
 * Has no actual use by itself, however each of its children are
 * used to excecute a project.
 */

#ifndef EXPLORER_MANAGER_H
#define EXPLORER_MANAGER_H

#include <fail_handler.h>

class InputHandler;

namespace explorer
{

class Manager
{
public:
  /// Primary constructor
  /**
   * Every project manager uses this constructor.
   * @param[in] inputHandler Every created project manager requires a
   *       reference to an InputHandler.
   */
  Manager(InputHandler& inputHandler);

  /// Executes the primary functionality of children classes.
  virtual void run();

protected:
  FailHandler fail_;
  InputHandler& inputHandler_;

};

}

#endif