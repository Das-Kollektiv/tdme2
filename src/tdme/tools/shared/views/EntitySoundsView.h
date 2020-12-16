
#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using std::vector;
using std::string;


using tdme::engine::Engine;
using tdme::tools::shared::controller::PrototypeSoundsSubScreenController;
using tdme::engine::prototype::Prototype;
using tdme::tools::shared::views::PopUps;

/**
 * Entity sounds view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntitySoundsView final
{
private:
	Engine* engine {  };
	PrototypeSoundsSubScreenController* prototypeSoundsSubScreenController {  };
	PopUps* popUps {  };

public:
	/**
	 * Public constructor
	 * @param prototypeSoundsSubScreenController entity sounds sub screen controller
	 * @param popUps pop ups
	 */
	EntitySoundsView(PrototypeSoundsSubScreenController* prototypeSoundsSubScreenController, PopUps* popUps);

	/**
	 * @return pop ups view
	 */
	PopUps* getPopUpsViews();

	/**
	 * Unset sounds
	 */
	void unsetSounds();

	/**
	 * Set sounds
	 * @param entity
	 */
	void setSounds(Prototype* entity);

};
