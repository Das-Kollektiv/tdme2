/*********************************************************************************
 * This source code is based on                                                  *
 * ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
 * Copyright (c) 2010-2015 Daniel Chappuis                                       *
 *********************************************************************************
 *                                                                               *
 * This software is provided 'as-is', without any express or implied warranty.   *
 * In no event will the authors be held liable for any damages arising from the  *
 * use of this software.                                                         *
 *                                                                               *
 * Permission is granted to anyone to use this software for any purpose,         *
 * including commercial applications, and to alter it and redistribute it        *
 * freely, subject to the following restrictions:                                *
 *                                                                               *
 * 1. The origin of this software must not be misrepresented; you must not claim *
 *    that you wrote the original software. If you use this software in a        *
 *    product, an acknowledgment in the product documentation would be           *
 *    appreciated but is not required.                                           *
 *                                                                               *
 * 2. Altered source versions must be plainly marked as such, and must not be    *
 *    misrepresented as being the original software.                             *
 *                                                                               *
 * 3. This notice may not be removed or altered from any source distribution.    *
 *                                                                               *
 ********************************************************************************/

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
