#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

#include <tdme/tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::string;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUITextNode;
using agui::utilities::MutableString;

using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;

/**
 * Info dialog screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::InfoDialogScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIFocusListener
	, public virtual GUITooltipRequestListener
{

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* tabsHeaderNode { nullptr };
	GUIStyledTextNode* messageNode { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(InfoDialogScreenController)

	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	InfoDialogScreenController(PopUps* popUps);

	/**
	 * Destructor
	 */
	virtual ~InfoDialogScreenController();

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
	 * Shows the pop up
	 */
	void show(const string& caption, const string& message);
	/**
	 * Closes the pop up
	 */
	void close();

};
