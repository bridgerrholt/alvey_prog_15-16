// Given a selected project, selects the correct manager and polymorphically
// creates it (on the heap due to polymorphism) and returns it.

#ifndef MAKE_MANAGER_H
#define MAKE_MANAGER_H

#include <memory>

#include "manager.h"
#include "project_identifier.h"

// Returns the polymorphic variable, std::move() is not necessary.
std::unique_ptr<explorer::Manager> makeManager(
  // All project managers inherit from explorer::Manager,
  // requiring a passed manager for construction.
  const explorer::Manager& baseManager,
  ProjectIdentifier projectIdentifier);

#endif