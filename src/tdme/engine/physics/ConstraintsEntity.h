// Generated from /tdme/src/tdme/engine/physics/ConstraintsEntity.java

#pragma once

#include <array>
#include <vector>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <java/lang/Object.h>

using std::array;
using std::vector;

using java::lang::Object;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::String;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::DynamicVector;
using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6, ::java::lang::ObjectArray > Matrix1x6Array;
}  // namespace physics
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math

namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Matrix1x6ArrayArray;
}  // namespace physics
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using tdme::engine::physics::Matrix1x6Array;
using tdme::engine::physics::Matrix1x6ArrayArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Physics constraints entity
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::ConstraintsEntity final
	: public Object
{

public:
	typedef Object super;

private:
	static constexpr float HITPOINT_TOLERANCE { 0.3f };

public: /* protected */
	RigidBody* rb1 {  };
	RigidBody* rb2 {  };
	CollisionResponse* collision {  };

private:
	array<Vector3*, 2> frictionVectors {{ new Vector3(), new Vector3() }};
	float muMg {  };
	Vector3* tmpVector3 {  };
	Vector3* r1 {  };
	Vector3* r2 {  };
	Vector3* r1CrossN {  };
	Vector3* r2CrossN {  };
	Vector3* r1CrossU1 {  };
	Vector3* r2CrossU1 {  };
	Vector3* r1CrossU2 {  };
	Vector3* r2CrossU2 {  };

	/** 
	 * Compute cross product a x b = dest
	 * @param a
	 * @param b
	 * @param dest
	 */
	static void computeCrossProduct(Vector3* a, Vector3* b, Vector3* dest);
protected:

	/** 
	 * Protected constructor
	 */
	void ctor();

public: /* protected */

	/** 
	 * Protected constructor
	 * @param rb1
	 * @param rb2
	 * @param collision
	 */
	void set(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision);

	/** 
	 * Compute jacobian
	 * @param constraint idx
	 * @param jacobian matrices
	 */
	void computeJacobian(int32_t constraintIdx, vector<array<Matrix1x6*, 2>>* jacobianMatrices);

	/** 
	 * Compute lower bounds
	 * @param constraint idx
	 * @param lower bounds
	 */
	void computeLowerBound(int32_t constraintIdx, DynamicVector* lowerBounds);

	/** 
	 * Create upper bounds
	 * @param constraint idx
	 * @param upper bounds
	 */
	void computeUpperBound(int32_t constraintIdx, DynamicVector* upperBounds);

	/** 
	 * Compute baumgarte
	 * @param constraint idx
	 * @param error values
	 */
	void computeBaumgarte(int32_t constraintIdx, DynamicVector* errorValues);

public:
	String* toString() override;

	// Generated

public: /* protected */
	ConstraintsEntity();
protected:
	ConstraintsEntity(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
