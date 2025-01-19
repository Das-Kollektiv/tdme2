#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUIInputEventHandler.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Properties.h>

using std::string;
using std::unordered_map;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIChangeListener;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUIInputEventHandler;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIScreenNode;
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
	struct MinitScriptMethodSelectionListener {
		virtual ~MinitScriptMethodSelectionListener() {}
		virtual void onMethodSelection(const string& methodName) = 0;
	};

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* contextMenuNode { nullptr };
	unordered_map<string, Action*> actions;

	Properties tscriptMethods;

	MinitScriptMethodSelectionListener* minitScriptMethodSelectionListener { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ContextMenuScreenController)

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
	 * Set MinitScript method selection listener
	 * @param minitScriptMethodSelectionListener MinitScript method selection listener
	 */
	inline void setMinitScriptMethodSelectionListener(MinitScriptMethodSelectionListener* minitScriptMethodSelectionListener) {
		this->minitScriptMethodSelectionListener = minitScriptMethodSelectionListener;
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
