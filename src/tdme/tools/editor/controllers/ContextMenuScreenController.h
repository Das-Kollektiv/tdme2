#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Properties.h>

using std::string;
using std::unordered_map;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;
using tdme::utilities::Properties;

/**
 * Context menu screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::ContextMenuScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIChangeListener
	, public virtual GUIFocusListener
	, public virtual GUITooltipRequestListener
	, public virtual GUIInputEventHandler
{
public:
	struct MiniScriptMethodSelectionListener {
		virtual ~MiniScriptMethodSelectionListener() {}
		virtual void onMethodSelection(const string& methodName) = 0;
	};

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* contextMenuNode { nullptr };
	unordered_map<string, Action*> actions;

	Properties tscriptMethods;

	MiniScriptMethodSelectionListener* miniScriptMethodSelectionListener { nullptr };

public:
	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	ContextMenuScreenController(PopUps* popUps);

	/**
	 * Destructor
	 */
	virtual ~ContextMenuScreenController();

	/**
	 * Set MiniScript method selection listener
	 * @param miniScriptMethodSelectionListener MiniScript method selection listener
	 */
	inline void setMiniScriptMethodSelectionListener(MiniScriptMethodSelectionListener* miniScriptMethodSelectionListener) {
		this->miniScriptMethodSelectionListener = miniScriptMethodSelectionListener;
	}

	/**
	 * Clear
	 */
	void clear();

	/**
	 * Clear and setup visual code add node context menu
	 */
	void setupVisualCodeAddNodeContextMenu();

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

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onChange(GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;
	void handleInputEvents() override;

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
