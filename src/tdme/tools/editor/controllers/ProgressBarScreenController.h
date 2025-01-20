#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

#include <tdme/tdme.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::string;

using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::utilities::MutableString;

using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;

/**
 * Progress bar screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::ProgressBarScreenController final
	: public ScreenController
	, public GUITooltipRequestListener
{

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* progressBarNode { nullptr };
	GUIElementNode* progressBarParent { nullptr };
	GUITextNode* progressMessageNode { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ProgressBarScreenController)

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
