#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>

using tdme::engine::subsystems::object::ModelUtilitiesInternal;

/** 
 * Model statistics class
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::object::ModelStatistics
{	int32_t opaqueFaceCount {  };
	int32_t transparentFaceCount {  };
	int32_t materialCount {  };
};
