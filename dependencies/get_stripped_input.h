// Gets the full input and strips out any white space margin.

#ifndef GET_STRIPPED_INPUT_H
#define GET_STRIPPED_INPUT_H

#include <string>

std::string getStrippedInput();
std::string getStrippedInput(std::string question, std::string ending = "");

#endif