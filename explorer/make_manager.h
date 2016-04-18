/// Creates, and returns a pointer to, the specified manager.
/**
 * Given a ProjectIdentifier, selects the correct manager and creates it in a
 * smart pointer of the base Manager class. The smart pointer is returned,
 * std::move is not necessary. The passed Manager is used in the creation of
 * the specified manager.
 *
 * @param[in] baseManager All project managers inherit from explorer::Manager,
 *       and require a passed explorer::Manager for construction.
 * @param[in] projectIdentifier An enum representing which project manager
 *       should be created.
 */

#ifndef MAKE_MANAGER_H
#define MAKE_MANAGER_H

#include <memory>

#include "manager.h"
#include "project_identifier.h"

std::unique_ptr<explorer::Manager> makeManager(
  const explorer::Manager& baseManager,
  ProjectIdentifier projectIdentifier);

#endif