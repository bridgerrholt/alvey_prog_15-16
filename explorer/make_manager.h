#ifndef MAKE_MANAGER_H
#define MAKE_MANAGER_H

#include "manager.h"
#include "project_identifier.h"

explorer::Manager* makeManager(
	const explorer::Manager& baseManager,
	ProjectIdentifier projectIdentifier);

#endif