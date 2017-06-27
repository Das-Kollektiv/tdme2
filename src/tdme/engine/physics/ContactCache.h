// Generated from /tdme/src/tdme/engine/physics/ContactCache.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ContactCache_ContactCacheInfo;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;
using tdme::utils::Key;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::ContactCache_ContactCacheInfo, ::java::lang::ObjectArray > ContactCache_ContactCacheInfoArray;
}  // namespace physics
}  // namespace engine

namespace utils {
typedef ::SubArray< ::tdme::utils::Key, ::java::lang::ObjectArray > KeyArray;
}  // namespace utils
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::physics::ContactCache_ContactCacheInfoArray;
using tdme::utils::KeyArray;

struct default_init_tag;

/** 
 * Contact cache manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::ContactCache final
	: public Object
{

public:
	typedef Object super;

private:
	Key* key {  };
	int32_t keyPoolIdx {  };
	KeyArray* keyPool {  };
	int32_t contactCacheInfoPoolIdx {  };
	ContactCache_ContactCacheInfoArray* contactCacheInfoPool {  };
	_HashMap* contactCache {  };
	Vector3* tmpVector3 {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor();

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
	void add(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision, floatArray* lamdaValues);

	/** 
	 * Retrieve contact cache info
	 * @param rigid body1
	 * @param rigid body2
	 * @param collision response
	 * @return contact cache info
	 */
	ContactCache_ContactCacheInfo* get(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision);

	// Generated
	ContactCache();
protected:
	ContactCache(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class ContactCache_ContactCacheInfo;
};
