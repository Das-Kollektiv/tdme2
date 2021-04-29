#pragma once

#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIScreenNode;

/**
 * Tab controller, which connects UI with logic
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::tools::editor::tabcontrollers::TabController: public GUIActionListener, public GUIChangeListener

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
