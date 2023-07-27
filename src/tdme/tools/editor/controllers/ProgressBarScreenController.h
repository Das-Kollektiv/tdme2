#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::MutableString;

/**
 * Progress bar screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::ProgressBarScreenController final
	: public ScreenController
	, public virtual GUITooltipRequestListener
{

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* progressBarNode { nullptr };
	GUIElementNode* progressBarParent { nullptr };
	GUITextNode* progressMessageNode { nullptr };

public:
	// forbid class copy
	CLASS_FORBID_COPY(ProgressBarScreenController)

	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	ProgressBarScreenController(PopUps* popUps);

	/**
	 * Destructor
	 */
	virtual ~ProgressBarScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;

	/**
	 * Shows the pop up
	 * @param showProgressBar show progress bar
	 */
	void show(const string& message, bool showProgressBar = true);

	/**
	 * Show progress
	 * @param value value
	 */
	void progress(float value);

	/**
	 * Show progress 2
	 * @param value value
	 */
	void progress2(float value);

	/**
	 * Closes the pop up
	 */
	void close();

};
