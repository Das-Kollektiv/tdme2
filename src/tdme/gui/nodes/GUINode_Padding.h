#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

/** 
 * Padding
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::nodes::GUINode_Padding
{

	int32_t left {  };
	int32_t top {  };
	int32_t right {  };
	int32_t bottom {  };
};
