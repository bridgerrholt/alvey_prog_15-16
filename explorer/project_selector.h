// Provides functionality for easily checking which project the user wants.

#ifndef PROJECT_SELECTOR_H
#define PROJECT_SELECTOR_H

#include <vector>
#include <string>

#include "project_identifier.h"

namespace explorer
{

class ProjectSelector
{
  public:
    // Represents names for a single project, i.e. what the user can enter
    // in order to select the desired project (the user can also enter the
    // ID listed with all the projects).
    class Project {
      public:
        // Both strings are valid input for the given project.
        std::string primary;
        std::string secondary;

        // Identifies which project the object is meant to represent.
        ProjectIdentifier identifier;
    };

    // Takes all the information needed for the creation of a Project object,
    // which is then pushed to the Project list.
    void pushProject(
      const std::string& primary,
      const std::string& secondary,
      ProjectIdentifier projectIdentifier);
    // Takes an already-created project and pushes it.
    void pushProject(const Project& projectToPush);

    std::string getFormattedProjects();

    // Based on a passed input, checks if it matches any project. If it does
    // match a project, return true and set the passed reference to that
    // project's identifier. If it does not match a project, return false.
    bool findProject(
      const std::string& input,
      // May be modified.
      ProjectIdentifier& projectIdentifierReturn);


  private:
    // All the projects registered in the program.
    std::vector<Project> projects_;
};

}

#endif