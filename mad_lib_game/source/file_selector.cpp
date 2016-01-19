#include "file_selector.h"

#include <iostream>
#include <string>
#include <vector>

#include "rand_range.h"

FileSelector::FileSelector() : path_("")
{

}



FileSelector::FileSelector(const std::string& path) : path_(path)
{

}



void FileSelector::pushFileName(std::string fileName)
{
	// Push the index of the new file name.
	remainingIndexes_.push_back(fileNames_.size());

	// Push the file name.
	fileNames_.push_back(path_ + fileName);
}



std::string FileSelector::getRandomFileName()
{
	// If the player has already cycled through all the file names,
	// reset the cycle.
	if (remainingIndexes_.size() <= 0) {
		for (std::size_t i = 0; i < fileNames_.size(); ++i) {
			remainingIndexes_.push_back(i);
		}
	}

	// Get a random index from the remainingIndexes_ container.
	std::size_t index = randRange(0, remainingIndexes_.size());
	// Get the index from the container.
	std::size_t fileNameIndex = remainingIndexes_[index];
	// Erase it from the remainingIndexes_ container.
	remainingIndexes_.erase(remainingIndexes_.begin()+index);

	// Return the file name.
	return fileNames_[fileNameIndex];
}