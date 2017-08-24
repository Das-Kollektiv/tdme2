// Generated from /tdme/src/tdme/engine/physics/ContactCache.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ContactCache_ContactCacheInfo;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;
using tdme::utils::Key;

/** 
 * Contact cache manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::ContactCache final
{
	friend class ContactCache_ContactCacheInfo;

private:
	map<wstring, ContactCache_ContactCacheInfo> contactCache {  };

public: /* protected */

	/** 
	 * Clear contact cache
	 */
	void clear();

	/** 
	 * @param rb1
	 * @param rb2
	 * @param collision
	 * @param lamdaValues
	 */
	void add(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision, vector<float>* lamdaValues);

	/** 
	 * Retrieve contact cache info
	 * @param rigid body1
	 * @param rigid body2
	 * @param collision response
	 * @return contact cache info
	 */
	ContactCache_ContactCacheInfo* get(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision);

	/**
	 * Constructor
	 */
	ContactCache();
};
