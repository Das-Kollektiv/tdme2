// Generated from /tdme/src/tdme/engine/physics/ContactCache.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/ContactCache_ContactCacheInfo.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ContactCache_ContactCacheInfo;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;

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
	inline void clear() {
		contactCache.clear();
	}

	/** 
	 * @param rb1
	 * @param rb2
	 * @param collision
	 * @param lamdaValues
	 */
	inline void add(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision, vector<float>* lamdaValues) {
		ContactCache_ContactCacheInfo contactCacheInfo;
		contactCacheInfo.rb1 = rb1;
		contactCacheInfo.rb2 = rb2;
		contactCacheInfo.hitPoints = *collision->getHitPoints();
		contactCacheInfo.lamdas = *lamdaValues;
		wstring key = rb1->id + L"," + rb2->id;
		contactCache[key] = contactCacheInfo;
	}

	/** 
	 * Retrieve contact cache info
	 * @param rigid body1
	 * @param rigid body2
	 * @param collision response
	 * @return contact cache info
	 */
	inline ContactCache_ContactCacheInfo* get(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision) {
		wstring key = rb1->id + L"," + rb2->id;
		ContactCache_ContactCacheInfo* contactCacheInfo = nullptr;
		auto contactCacheInfoIt = contactCache.find(key);
		if (contactCacheInfoIt != contactCache.end()) {
			contactCacheInfo = &contactCacheInfoIt->second;
		}
		if (contactCacheInfo != nullptr) {
			if (collision->getHitPointsCount() != contactCacheInfo->hitPoints.size()) return nullptr;
			Vector3 tmpVector3;
			for (auto i = 0; i < contactCacheInfo->hitPoints.size(); i++) {
				tmpVector3.set(collision->getHitPointAt(i))->sub(&contactCacheInfo->hitPoints[i]);
				if (tmpVector3.computeLength() > 0.1f) return nullptr;
			}
			return contactCacheInfo;
		}
		return nullptr;
	}

	/**
	 * Constructor
	 */
	inline ContactCache() {
	}
};
