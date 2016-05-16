#include "project_selector.h"

#include <patch/to_string.h>
#include <get_lowered.h>

using namespace explorer;

void ProjectSelector::pushProject(
  const std::string& primary,
  const std::string& secondary,
  ProjectIdentifier projectIdentifier)
{
  projects_.push_back({primary, secondary, projectIdentifier});
}

void ProjectSelector::pushProject(const Project& projectToPush)
{
  projects_.push_back(projectToPush);
}



std::string ProjectSelector::getFormattedProjects()
{
  // Format is as follows:
  //| 1: Project1
  //| 2: Project2
  //| ...

  std::string toReturn = "";

  // Loop through each project, concat-ing its number and information.
  for (auto i = projects_.begin(); i != projects_.end(); ++i) {
    toReturn += " " +
      // The number (not index, starts at 1) given to the project.
      patch::to_string(i - projects_.begin() + 1) +
      // Only the primary string is outputted.
      ": " + i->primary + "\n";
  }

  return toReturn;
}



bool ProjectSelector::findProject(
  const std::string& input, ProjectIdentifier& projectIdentifierReturn)
{
  // Loop through each project.
  for (auto i = projects_.begin(); i != projects_.end(); ++i) {
    // Reuse the output instead of making a new variable, faster and
    // allows better error checking.
    //projectIndex = i - projects_.begin();

    // Check the input against each project's valid names.
    if (input == patch::to_string(i - projects_.begin() + 1) ||
        input == getLowered(i->primary) ||
        input == getLowered(i->secondary)) {

      // Set the identifier and return true to indicate success.
      projectIdentifierReturn = i->identifier;
      return true;
    }
  }

  // No project indicated by the given input was found.
  return false;
}
