// Generated from /tdme/src/tdme/engine/physics/ContactCache.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::vector;

using java::lang::Object;
using tdme::engine::physics::ContactCache;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;
using tdme::utils::Key;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Contact cache info
 */
class tdme::engine::physics::ContactCache_ContactCacheInfo
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	Key* key {  };
	RigidBody* rb1 {  };
	RigidBody* rb2 {  };
	int32_t hitPointCount {  };
	vector<Vector3*> hitPoints {  };
	floatArray* lamdas {  };

	// Generated

public:
	ContactCache_ContactCacheInfo();
protected:
	ContactCache_ContactCacheInfo(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class ContactCache;
};
