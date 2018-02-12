
#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::utils::MutableString;

/** 
 * Entity display sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::EntityDisplaySubScreenController
{
private:
	static MutableString CHECKBOX_CHECKED;
	static MutableString CHECKBOX_UNCHECKED;
	GUIElementNode* displayBoundingVolume {  };
	GUIElementNode* displayShadowing {  };
	GUIElementNode* displayGround {  };
	EntityDisplayView* view {  };

public:

	/** 
	 * @return view
	 */
	virtual EntityDisplayView* getView();

	/** 
	 * Init
	 * @param screen node
	 */
	virtual void initialize(GUIScreenNode* screenNode);

	/** 
	 * Set up display section
	 */
	virtual void setupDisplay();

	/** 
	 * On display apply button event
	 */
	virtual void onDisplayApply();

	/** 
	 * @return display shadowing checked
	 */
	virtual bool getDisplayShadowing();

	/** 
	 * @return display ground checked
	 */
	virtual bool getDisplayGround();

	/** 
	 * @return display bounding volume checked
	 */
	virtual bool getDisplayBoundingVolume();
	virtual void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node);

	/**
	 * Public constructor
	 */
	EntityDisplaySubScreenController();

	/**
	 * Destructor
	 */
	virtual ~EntityDisplaySubScreenController();
};
