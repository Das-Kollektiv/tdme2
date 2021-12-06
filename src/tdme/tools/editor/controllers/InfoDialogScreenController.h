#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::utilities::MutableString;

/**
 * Info dialog screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::controllers::InfoDialogScreenController final
	: public ScreenController
	, public virtual GUIActionListener
{

private:
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* tabsHeaderNode { nullptr };
	GUIMultilineTextNode* messageNode { nullptr };

public:
	/**
	 * Public constructor
	 */
	InfoDialogScreenController();

	/**
	 * Destructor
	 */
	virtual ~InfoDialogScreenController();

	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;

	/**
	 * Shows the pop up
	 */
	void show(const string& caption, const string& message);
	/**
	 * Closes the pop up
	 */
	void close();

};
