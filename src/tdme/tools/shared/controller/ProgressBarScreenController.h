
#pragma once

#include <string>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>

using std::string;

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::MutableString;

/** 
 * Progress bar screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::ProgressBarScreenController
	: public ScreenController
{

private:
	GUIScreenNode* screenNode {  };
	GUIElementNode* progressBarNode {  };

public:
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;

	/** 
	 * Shows the pop up
	 */
	virtual void show();

	/**
	 * Show progress
	 * @param value value
	 */
	virtual void progress(float value);

	/** 
	 * Closes the pop up
	 */
	virtual void close();

	/**
	 * Public constructor
	 */
	ProgressBarScreenController();

	/**
	 * Destructor
	 */
	virtual ~ProgressBarScreenController();
};
