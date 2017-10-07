#pragma once

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>

using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUINode;


struct default_init_tag;

/** 
 * GUI button controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIButtonController final
	: public GUIElementController
{

public:
	typedef GUIElementController super;

protected:

	/** 
	 * GUI button controller
	 * @param node
	 */
	void ctor(GUINode* node);

	// Generated

public: /* protected */
	GUIButtonController(GUINode* node);
protected:
	GUIButtonController(const ::default_init_tag&);
};
