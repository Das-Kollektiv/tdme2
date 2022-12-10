#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIScreenNode;

/**
 * Tab controller, which connects UI with logic
 * @author Andreas Drewke
 */
struct tdme::tools::editor::tabcontrollers::TabController:
	public GUIActionListener,
	public GUIChangeListener,
	public GUIFocusListener,
	public GUIContextMenuRequestListener,
	public GUITooltipRequestListener
{
	enum TabControllerCommand { COMMAND_SAVE, COMMAND_SAVEAS, COMMAND_UNDO, COMMAND_REDO, COMMAND_CUT, COMMAND_COPY, COMMAND_PASTE, COMMAND_DELETE, COMMAND_SELECTALL, COMMAND_FINDREPLACE};

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

	/**
	 * On command
	 * @param command command
	 */
	virtual void onCommand(TabControllerCommand command) = 0;

	/**
	 * On drop
	 * @param payload payload
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 */
	virtual void onDrop(const string& payload, int mouseX, int mouseY) = 0;

};
