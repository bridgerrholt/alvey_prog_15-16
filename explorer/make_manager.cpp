#include "make_manager.h"

#include "binary_search/manager.h"
#include "encryption/manager.h"
#include "game_of_pig/manager.h"
#include "hang_man/manager.h"
#include "mad_lib_game/manager.h"

explorer::Manager* makeManager(
	const explorer::Manager& baseManager,
	ProjectIdentifier projectIdentifier)
{
	switch (projectIdentifier) {
	case BINARY_SEARCH:
		return
			new binary_search::Manager(baseManager);
		break;
	case ENCRYPTION:
		return
			new encryption::Manager(baseManager);
		break;
	case GAME_OF_PIG:
		return
			new game_of_pig::Manager(baseManager, 100);
		break;
	case HANG_MAN:
		return
			new hang_man::Manager(baseManager,
			"../../dictionaries/american-english-no-accents.txt",
			"text_images/man.txt");
		break;
	case MAD_LIB_GAME:
		return
			new mad_lib::Manager(baseManager, "projects/mad_lib_game/stories/");
		break;
	default:
		return 0;
	}
}