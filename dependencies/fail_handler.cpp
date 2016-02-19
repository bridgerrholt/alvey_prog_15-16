#include "fail_handler.h"

#include <iostream>

FailHandler::FailHandler() : fail_(false)
{

}



void FailHandler::error(const std::string& errorString)
{
	std::cout << errorString;
	fail_ = true;
}



void FailHandler::reset()
{
	fail_ = false;
}



bool FailHandler::get()
{
	return fail_;
}