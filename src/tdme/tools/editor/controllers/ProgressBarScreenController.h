#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::utilities::MutableString;

/**
 * Progress bar screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::controllers::ProgressBarScreenController final
	: public ScreenController
{

private:
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* progressBarNode { nullptr };
	GUIElementNode* progressBarParent { nullptr };
	GUITextNode* progressMessageNode { nullptr };

public:
	/**
	 * Public constructor
	 */
	ProgressBarScreenController();

	/**
	 * Destructor
	 */
	virtual ~ProgressBarScreenController();

	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;

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
