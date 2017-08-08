// Generated from /tdme/src/tdme/engine/subsystems/object/AnimationState.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>

using tdme::engine::model::AnimationSetup;
/** 
 * Animation state class
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::object::AnimationState final {
	AnimationSetup* setup {  };
	int64_t currentAtTime {  };
	int64_t lastAtTime {  };
	bool finished {  };
	float time {  };
};
