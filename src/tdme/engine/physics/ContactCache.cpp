#include <tdme/engine/physics/ContactCache.h>

#include <map>
#include <string>

#include <java/lang/String.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/ConstraintsSolver.h>
#include <tdme/engine/physics/ContactCache_ContactCacheInfo.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/math/Vector3.h>

using std::map;
using std::wstring;

using tdme::engine::physics::ContactCache;
using java::lang::String;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ConstraintsSolver;
using tdme::engine::physics::ContactCache_ContactCacheInfo;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;
using tdme::utils::Key;

ContactCache::ContactCache() 
{
}

void ContactCache::clear()
{
	contactCache.clear();
}

void ContactCache::add(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision, vector<float>* lamdaValues)
{
	ContactCache_ContactCacheInfo contactCacheInfo;
	contactCacheInfo.rb1 = rb1;
	contactCacheInfo.rb2 = rb2;
	contactCacheInfo.hitPoints = *collision->getHitPoints();
	contactCacheInfo.lamdas = *lamdaValues;
	wstring key = rb1->id + L"," + rb2->id;
	contactCache[key] = contactCacheInfo;
}

ContactCache_ContactCacheInfo* ContactCache::get(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision)
{
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
