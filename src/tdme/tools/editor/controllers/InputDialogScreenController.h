#pragma once

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/fwd-agui.h>

#include <tdme/tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unique_ptr;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIChangeListener;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;

using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;

/**
 * Input dialog screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::InputDialogScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIChangeListener
	, public virtual GUIFocusListener
	, public virtual GUITooltipRequestListener
{

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* tabsHeaderNode { nullptr };
	GUIElementNode* inputNode { nullptr };
	unique_ptr<Action> applyAction;
	unique_ptr<Action> cancelAction;

public:
	// forbid class copy
	FORBID_CLASS_COPY(InputDialogScreenController)

	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	InputDialogScreenController(PopUps* popUps);

	/**
	 * Destructor
	 */
	virtual ~InputDialogScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;

	/**
	 * @returns input text
	 */
	const string getInputText();

	/**
	 * Shows the input dialog pop up
	 * @param captionText caption text
	 * @param inputText input text
	 * @param applyAction apply action
	 * @param cancelAction cancel action
	 */
	void show(const string& captionText, const string& inputText, Action* applyAction, Action* cancelAction = nullptr);

	/**
	 * Abort the file dialog pop up
	 */
	void close();

	// overridden methods
	void initialize() override;
	void dispose() override;
	void onChange(GUIElementNode* node) override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;

};
