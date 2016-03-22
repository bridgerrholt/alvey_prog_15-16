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
	printData();

	// If the player has already cycled through all the file names,
	// reset the cycle.
	if (remainingIndexes_.size() == 0) {
		for (std::size_t i = 0; i < fileNames_.size(); ++i) {
			// Don't add the file if it's being prevented.
			if (!(isPreventingFile_ && preventedFileIndex_ == i))
				remainingIndexes_.push_back(i);
			else
				std::cout << "Didn't push " << i << '\n';
		}
	}

	printData();
	// Get a random index from the remainingIndexes_ container.
	std::size_t index = randRange(0, remainingIndexes_.size());
	// Get the index from the container.
	std::size_t fileNameIndex = remainingIndexes_[index];
	// Erase it from the remainingIndexes_ container.
	remainingIndexes_.erase(remainingIndexes_.begin()+index);
	printData();

	// If a file was prevented, it will be added once preventing the current\
	// file (if its the last in the cycle).
	bool toAddFile = isPreventingFile_;
	std::size_t fileToAddIndex = preventedFileIndex_;
	isPreventingFile_ = false;

	// If the cycle is finished, prevent the current file from being added
	// to the new cycle the next run.
	if (remainingIndexes_.size() == 0) {
		// Don't prevent it if there's only 1 file.
		if (fileNames_.size() > 1) {
			isPreventingFile_ = true;
			preventedFileIndex_ = fileNameIndex;
		}
	}

	// Once the next file has been selected, the prevented file can be added back to the loop
	if (toAddFile) {
		remainingIndexes_.push_back(fileToAddIndex);
	}

	printData();

	// Return the file name.
	return fileNames_[fileNameIndex];
}



void FileSelector::printData()
{
	std::cout << "[";
	std::size_t index = 0;
	while (index+1 < remainingIndexes_.size()) {
		std::cout << remainingIndexes_[index] << ", ";

		++index;
	}
	if (remainingIndexes_.size() > 0) {
		std::cout << remainingIndexes_[index];
	}
	std::cout << "]\n";

	if (isPreventingFile_)
		std::cout << "Preventing " << preventedFileIndex_ << '\n';
}
