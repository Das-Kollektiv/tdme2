#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::utilities::Action;

/**
 * Context menu screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::controllers::ContextMenuScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIFocusListener
{

private:
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* contextMenuNode { nullptr };
	unordered_map<string, Action*> actions;

public:
	/**
	 * Public constructor
	 */
	ContextMenuScreenController();

	/**
	 * Destructor
	 */
	virtual ~ContextMenuScreenController();

	/**
	 * Clear
	 */
	void clear();

	/**
	 * Add menu item
	 * @param text text
	 * @param id id
	 * @param action action
	 */
	void addMenuItem(const string& text, const string& id, Action* action = nullptr);

	/**
	 * Add menu separator
	 */
	void addMenuSeparator();

	// overriden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;

	/**
	 * Shows the pop up
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 */
	void show(int mouseX, int mouseY);

	/**
	 * Closes the pop up
	 */
	void close();

};
