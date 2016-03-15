#include "project_selector.h"

#include <patch/to_string.h>
#include <get_lowered.h>

using namespace explorer;

ProjectSelector::ProjectSelector()
{
	
}



void ProjectSelector::pushProject(std::string primary, std::string secondary)
{
	projects_.push_back({primary, secondary});
}



std::string ProjectSelector::getFormattedProjects()
{
	std::string toReturn = "";

	// Loop through each project, concat-ing its number and information.
	for (auto i = projects_.begin(); i != projects_.end(); ++i) {
		toReturn += " ";
		toReturn += patch::to_string(i - projects_.begin() + 1);
		toReturn += ": ";
		toReturn += i->primary;
		toReturn += "\n";
	}

	return toReturn;
}



bool ProjectSelector::findProject(
	std::string input, std::size_t& projectIndex)
{
	// Loop through each project.
	for (auto i = projects_.begin(); i != projects_.end(); ++i) {
		// Reuse the output instead of making a new variable, faster and
		// allows better error checking.
		projectIndex = i - projects_.begin();

		// Check each project's valid names.
		if (input == patch::to_string(projectIndex+1) ||
			input == getLowered(i->primary) ||
			input == getLowered(i->secondary)) {
			return true;
		}
	}

	// No project of name input was found.
	return false;
}


