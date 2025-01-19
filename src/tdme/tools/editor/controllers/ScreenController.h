#pragma once

#include <tdme/tdme.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>

using agui::gui::nodes::GUIScreenNode;

/**
 * Screen controller, which connects GUI screen definition with code
 * @author Andreas Drewke
 */
struct tdme::tools::editor::controllers::ScreenController
{
	/**
	 * Destructor
	 */
	virtual ~ScreenController() {}

	/**
	 * @returns screen node
	 */
	virtual GUIScreenNode* getScreenNode() = 0;

	/**
	 * Init
	 */
	virtual void initialize() = 0;

	/**
	 * Dispose
	 */
	virtual void dispose() = 0;

};
