#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>

using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;

/**
 * Prototype sounds view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView final
{
private:
	PrototypeSoundsSubController* prototypeSoundsSubController { nullptr };
	PopUps* popUps { nullptr };

public:
	/**
	 * Public constructor
	 * @param prototypeSoundsSubController entity sounds sub screen controller
	 * @param popUps pop ups
	 */
	PrototypeSoundsSubView(PrototypeSoundsSubController* prototypeSoundsSubController, PopUps* popUps);

	/**
	 * @returns pop ups
	 */
	PopUps* getPopUps();

};
