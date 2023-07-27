#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::controllers::ScreenController;
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
	Action* applyAction { nullptr };
	Action* cancelAction { nullptr };

public:
	// forbid class copy
	CLASS_FORBID_COPY(InputDialogScreenController)

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
	 * @return input text
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
