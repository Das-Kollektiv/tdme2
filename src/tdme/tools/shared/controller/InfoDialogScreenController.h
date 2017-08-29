// Generated from /tdme/src/tdme/tools/shared/controller/InfoDialogScreenController.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using java::lang::String;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::utils::MutableString;

/** 
 * Info dialog screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::InfoDialogScreenController
	: public ScreenController
	, public virtual GUIActionListener
{

private:
	GUIScreenNode* screenNode {  };
	GUITextNode* captionNode {  };
	GUITextNode* messageNode {  };
	MutableString* value {  };

public:
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;

	/** 
	 * Shows the pop up
	 */
	virtual void show(String* caption, String* message);

	/** 
	 * Closes the pop up
	 */
	virtual void close();
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	/**
	 * Public constructor
	 */
	InfoDialogScreenController();
};
