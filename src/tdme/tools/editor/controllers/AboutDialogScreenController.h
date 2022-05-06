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
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::utilities::MutableString;

/**
 * About dialog screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::AboutDialogScreenController final
	: public ScreenController
	, public virtual GUIActionListener
{

private:
	GUIScreenNode* screenNode { nullptr };

public:
	/**
	 * Public constructor
	 */
	AboutDialogScreenController();

	/**
	 * Destructor
	 */
	virtual ~AboutDialogScreenController();

	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;

	/**
	 * Shows the pop up
	 */
	void show();
	/**
	 * Closes the pop up
	 */
	void close();

};
