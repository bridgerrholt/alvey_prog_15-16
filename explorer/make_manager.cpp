#include "make_manager.h"

#include "binary_search/manager.h"
#include "encryption/manager.h"
#include "game_of_pig/manager.h"
#include "hang_man/manager.h"
#include "mad_lib_game/manager.h"

std::unique_ptr<explorer::Manager> makeManager(
  const explorer::Manager& baseManager,
  ProjectIdentifier projectIdentifier)
{
  // Dangerous raw pointer, gets collected by the return.
  explorer::Manager* heapManager = 0;

  switch (projectIdentifier) {
    case BINARY_SEARCH :
      heapManager = new binary_search::Manager(baseManager);
      break;

    case ENCRYPTION :
      heapManager = new encryption::Manager(baseManager);
      break;

    case GAME_OF_PIG :
      heapManager = new game_of_pig::Manager(baseManager, 100);
      break;

    case HANG_MAN :
      heapManager = new hang_man::Manager(baseManager,
        "../../dictionaries/american-english-no-accents.txt",
        "text_images/man.txt");
      break;

    case MAD_LIB_GAME :
      heapManager = new mad_lib::Manager(baseManager,
        "projects/mad_lib_game/stories/");
      break;

    // Should never be reached.
    default :
      throw std::runtime_error("Invalid ProjectIdentifier");
  }

  // Fail if the manager was somehow not correctly allocated. This should
  // never happen because the default case should catch anything anyway.
  if (heapManager == 0)
    throw std::runtime_error("Manager creation failed");

  // Collect the raw pointer to the allocated manager.
  return std::unique_ptr<explorer::Manager>(heapManager);
}