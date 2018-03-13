
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>

using tdme::engine::model::AnimationSetup;
/** 
 * Animation state class
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::rendering::AnimationState final {
	AnimationSetup* setup {  };
	int64_t currentAtTime {  };
	int64_t lastAtTime {  };
	bool finished {  };
	float time {  };
};
