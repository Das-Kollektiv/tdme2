// Generated from /tdme/src/tdme/engine/physics/ContactCache.java

#pragma once

#include <vector>
#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>

using std::wstring;
using std::vector;

using tdme::engine::physics::ContactCache;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;

/** 
 * Contact cache info
 */
struct tdme::engine::physics::ContactCache_ContactCacheInfo {
	wstring key {  };
	RigidBody* rb1 {  };
	RigidBody* rb2 {  };
	vector<Vector3> hitPoints {  };
	vector<float> lamdas {  };
};
