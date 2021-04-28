#pragma once

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>

using tdme::gui::nodes::GUIScreenNode;

/**
 * Tab controller, which connects UI with logic
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::tools::editor::tabcontrollers::TabController
{
	/**
	 * Destructor
	 */
	virtual ~TabController() {}

	/**
	 * Init
	 */
	virtual void initialize(GUIScreenNode* screenNode) = 0;

	/**
	 * Dispose
	 */
	virtual void dispose() = 0;

	// ???
	virtual GUIScreenNode* getScreenNode() = 0;

};
