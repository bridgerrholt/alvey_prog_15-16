#include <iostream>
#include <string>
#include <vector>

#include <rand_range.h>

#include "file_selector.h"

using namespace mad_lib;

FileSelector::FileSelector() :
	path_(""),
	isPreventingFile_(false)
{

}



FileSelector::FileSelector(const std::string& path) : FileSelector()
{
	path_ = path;
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
			// Don't add the file if it's being prevented.
			if (!(isPreventingFile_ && preventedFileIndex_))
				remainingIndexes_.push_back(i);
		}
	}

	isPreventingFile_ = false;

	// Get a random index from the remainingIndexes_ container.
	std::size_t index = randRange(0, remainingIndexes_.size());
	// Get the index from the container.
	std::size_t fileNameIndex = remainingIndexes_[index];
	// Erase it from the remainingIndexes_ container.
	remainingIndexes_.erase(remainingIndexes_.begin()+index);

	// If the cycle is finished, prevent the current file from being added
	// to the new cycle the next run.
	if (remainingIndexes_.size() == 0) {
		// Don't prevent it if there's only 1 file.
		if (fileNames_.size() > 1) {
			isPreventingFile_ = true;
			preventedFileIndex_ = fileNameIndex;
		}
	}

	// Return the file name.
	return fileNames_[fileNameIndex];
}




