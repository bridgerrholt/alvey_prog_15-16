// Holds the file names for all the stories,
// and returns randomly-selected ones.

#ifndef FILE_SELECTOR_H
#define FILE_SELECTOR_H

#include <string>
#include <vector>

class FileSelector
{
public:
	FileSelector();
	FileSelector(const std::string& path);

	// Pushes back a file name to the fileNames_ container.
	void pushFileName(std::string fileName);

	// Returns a random file name.
	std::string getRandomFileName();

	// Sets.
	void setPath(const std::string& path) { path_ = path; }

	// Gets.
	std::size_t getRemainingIndexesSize()
		const { return remainingIndexes_.size(); }

private:
	// Concatenated to the beginning of all future file name strings.
	std::string path_;

	// Holds all the file names for the text files.
	std::vector<std::string> fileNames_;

	// Indexes for file names that haven't been used yet.
	std::vector<std::size_t> remainingIndexes_;

};

#endif