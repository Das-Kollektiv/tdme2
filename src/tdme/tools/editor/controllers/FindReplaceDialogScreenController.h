#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <agui/utilities/fwd-agui.h>

using std::string;
using std::unique_ptr;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::events::GUIFocusListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;
using agui::utilities::MutableString;

/**
 * Find/Replace dialog screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::FindReplaceDialogScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIFocusListener
	, public virtual GUITooltipRequestListener
{

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* findText { nullptr };
	GUIElementNode* replaceText { nullptr };
	GUIElementNode* matchCase { nullptr };
	GUIElementNode* wholeWordOnly { nullptr };
	GUIElementNode* inSelectionOnly { nullptr };
	GUIElementNode* findButton { nullptr };
	GUIElementNode* countButton { nullptr };
	GUIElementNode* cancelButton { nullptr };
	GUIElementNode* replaceButton { nullptr };
	GUIElementNode* replaceAllButton { nullptr };

	unique_ptr<Action> findAction;
	unique_ptr<Action> countAction;
	unique_ptr<Action> replaceAction;
	unique_ptr<Action> replaceAllAction;
	unique_ptr<Action> completeAction;

public:
	// forbid class copy
	FORBID_CLASS_COPY(FindReplaceDialogScreenController)

	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	FindReplaceDialogScreenController(PopUps* popUps);

	/**
	 * Destructor
	 */
	virtual ~FindReplaceDialogScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;

	/**
	 * @returns find text
	 */
	const string getFindText();

	/**
	 * @returns replace text
	 */
	const string getReplaceText();

	/**
	 * @returns is match case checked
	 */
	bool isMatchCase();

	/**
	 * @returns is whole world only checked
	 */
	bool isWholeWordOnly();

	/**
	 * @returns is in selection only checked
	 */
	bool isInSelectionOnly();

	/**
	 * Shows the pop up
	 * @param findAction find action
	 * @param coundAction count action
	 * @param replaceAction replace action
	 * @param replaceAllAction replace all action
	 * @param completeAction complete action
	 */
	void show(Action* findAction, Action* countAction, Action* replaceAction, Action* replaceAllAction, Action* completeAction);
	/**
	 * Closes the pop up
	 */
	void close();

};
