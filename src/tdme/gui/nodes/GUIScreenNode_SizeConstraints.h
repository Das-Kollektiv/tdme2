#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

/** 
 * GUI screen node size constraints entity
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::nodes::GUIScreenNode_SizeConstraints
{

	int32_t minWidth {  };
	int32_t minHeight {  };
	int32_t maxWidth {  };
	int32_t maxHeight {  };

};
