// An object that runs one game when asked to.

#ifndef BINARY_SEARCH_MANAGER_H
#define BINARY_SEARCH_MANAGER_H

#include <string>

#include "../explorer/manager.h"

namespace binary_search
{

class Manager : public explorer::Manager
{
public:
  // Constructors.
  Manager(const explorer::Manager& baseManager);

  // Runs a single game.
  void run();

private:
  // The type of number to be used for the range.
  typedef long int Number;

  // Resets variables that must be fresh each run.
  void reset();

  // Asks if the given number is greater than or less than the
  // target number.
  void makeGuess();

  // All the error checking functions.
  void checkEmptyValue(std::string input, std::string name);
  void checkValueInteger(std::string input, std::string name);
  Number valueToNumber(std::string input, std::string name);

  // Sets the difference appropriately.
  void calculateDifference();

  // The range.
  Number min_;
  Number max_;
  Number difference_;

  // Incremented every time makeGuess is called.
  std::size_t guessCount_;

};

}

#endif