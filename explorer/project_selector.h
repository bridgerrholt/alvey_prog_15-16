// Provides functionality for easily checking which project the user wants.

#ifndef PROJECT_SELECTOR_H
#define PROJECT_SELECTOR_H

#include <vector>
#include <array>
#include <string>

namespace explorer
{

class ProjectSelector
{
public:
	//typedef std::vector<std::string> NameList;
	//typedef std::array<std::string, 2> NameList;

	ProjectSelector();

	void pushProject(std::string primary, std::string secondary);

	std::string getFormattedProjects();

	bool findProject(std::string input, std::size_t& projectIndex);


private:
	class Project {
	public:
		std::string primary;
		std::string secondary;
	};

	std::vector<Project> projects_;


};

}

#endif