#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;
using tdme::utilities::MutableString;

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

	Action* findAction { nullptr };
	Action* countAction { nullptr };
	Action* replaceAction { nullptr };
	Action* replaceAllAction { nullptr };
	Action* completeAction { nullptr };

public:
	// forbid class copy
	CLASS_FORBID_COPY(FindReplaceDialogScreenController)

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
	 * @return find text
	 */
	const string getFindText();

	/**
	 * @return replace text
	 */
	const string getReplaceText();

	/**
	 * @return is match case checked
	 */
	bool isMatchCase();

	/**
	 * @return is whole world only checked
	 */
	bool isWholeWordOnly();

	/**
	 * @return is in selection only checked
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
