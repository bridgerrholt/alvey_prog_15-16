// Provides functionality for easily checking which project the user wants.

#ifndef PROJECT_SELECTOR_H
#define PROJECT_SELECTOR_H

#include <vector>
#include <array>
#include <string>

#include "project_identifier.h"

namespace explorer
{

class ProjectSelector
{
public:
	//typedef std::vector<std::string> NameList;
	//typedef std::array<std::string, 2> NameList;

	ProjectSelector();

	void pushProject(std::string primary, std::string secondary,
		ProjectIdentifier projectIdentifier);

	std::string getFormattedProjects();

	bool findProject(std::string input, ProjectIdentifier& projectIdentifier);


private:
	class Project {
	public:
		std::string primary;
		std::string secondary;
		ProjectIdentifier identifier;
	};

	std::vector<Project> projects_;


};

}

#endif