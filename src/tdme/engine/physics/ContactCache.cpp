// Generated from /tdme/src/tdme/engine/physics/ContactCache.java
#include <tdme/engine/physics/ContactCache.h>

#include <map>
#include <string>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/ConstraintsSolver.h>
#include <tdme/engine/physics/ContactCache_ContactCacheInfo.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::map;
using std::wstring;

using tdme::engine::physics::ContactCache;
using java::lang::Object;
using java::lang::String;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ConstraintsSolver;
using tdme::engine::physics::ContactCache_ContactCacheInfo;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;
using tdme::utils::Key;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::ContactCache_ContactCacheInfo, ::java::lang::ObjectArray > ContactCache_ContactCacheInfoArray;
}  // namespace physics
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math

namespace utils {
typedef ::SubArray< ::tdme::utils::Key, ::java::lang::ObjectArray > KeyArray;
}  // namespace utils
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

ContactCache::ContactCache(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ContactCache::ContactCache() 
	: ContactCache(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void ContactCache::init()
{
	contactCacheInfoPoolIdx = 0;
	contactCacheInfoPool = nullptr;
	tmpVector3 = new Vector3();
}

void ContactCache::ctor()
{
	super::ctor();
	init();
	contactCacheInfoPool = new ContactCache_ContactCacheInfoArray(ConstraintsSolver::CONSTRAINTS_MAX);
	for (auto i = 0; i < ConstraintsSolver::CONSTRAINTS_MAX; i++) {
		contactCacheInfoPool->set(i, new ContactCache_ContactCacheInfo());
		(*contactCacheInfoPool)[i]->hitPoints = new Vector3Array(CollisionResponse::HITPOINT_COUNT);
		(*contactCacheInfoPool)[i]->lamdas = new floatArray(CollisionResponse::HITPOINT_COUNT * 3);
		for (auto j = 0; j < CollisionResponse::HITPOINT_COUNT; j++) {
			(*contactCacheInfoPool)[i]->hitPoints->set(j, new Vector3());
		}
	}
}

void ContactCache::clear()
{
	contactCacheInfoPoolIdx = 0;
	contactCache.clear();
}

void ContactCache::add(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision, floatArray* lamdaValues)
{
	auto contactCacheInfo = (*contactCacheInfoPool)[contactCacheInfoPoolIdx++];
	contactCacheInfo->rb1 = rb1;
	contactCacheInfo->rb2 = rb2;
	contactCacheInfo->hitPointCount = collision->getHitPointsCount();
	for (auto i = 0; i < contactCacheInfo->hitPointCount; i++) {
		(*contactCacheInfo->hitPoints)[i]->set(collision->getHitPointAt(i));
		(*contactCacheInfo->lamdas)[i] = (*lamdaValues)[i];
	}
	wstring key = rb1->id->getCPPWString() + L"," + rb2->id->getCPPWString();
	contactCache[key] = contactCacheInfo;
}

ContactCache_ContactCacheInfo* ContactCache::get(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision)
{
	wstring key = rb1->id->getCPPWString() + L"," + rb2->id->getCPPWString();
	ContactCache_ContactCacheInfo* contactCacheInfo = nullptr;
	auto contactCacheInfoIt = contactCache.find(key);
	if (contactCacheInfoIt != contactCache.end()) {
		contactCacheInfo = contactCacheInfoIt->second;
	}
	if (contactCacheInfo != nullptr) {
		if (collision->getHitPointsCount() != contactCacheInfo->hitPointCount)
			return nullptr;

		for (auto i = 0; i < contactCacheInfo->hitPointCount; i++) {
			tmpVector3->set(collision->getHitPointAt(i))->sub((*contactCacheInfo->hitPoints)[i]);
			if (tmpVector3->computeLength() > 0.1f)
				return nullptr;

		}
		return contactCacheInfo;
	}
	return nullptr;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ContactCache::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.ContactCache", 32);
    return c;
}

java::lang::Class* ContactCache::getClass0()
{
	return class_();
}

