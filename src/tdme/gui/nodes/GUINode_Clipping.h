#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUINode_Clipping;

/** 
 * GUI node clipping entity
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::nodes::GUINode_Clipping
{

	int32_t left {  };
	int32_t top {  };
	int32_t right {  };
	int32_t bottom {  };
};
