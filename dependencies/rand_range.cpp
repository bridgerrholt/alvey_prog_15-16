#include <cstdlib>
#include <iostream>

int randRange(int min, int max)
{
	return min + static_cast <int>(std::rand())/(static_cast <float>(RAND_MAX/(max-min))); 

	float returnVal = min + ((max * std::rand()) / (RAND_MAX + 1.0));
	std::cout << returnVal << '\n';
	return returnVal;
}