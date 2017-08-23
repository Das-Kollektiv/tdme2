// Generated from /tdme/src/tdme/engine/physics/ConstraintsSolver.java

#pragma once

#include <array>
#include <map>
#include <vector>
#include <string>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::array;
using std::map;
using std::vector;
using std::wstring;

using java::lang::Object;
using java::io::Serializable;
using java::lang::Cloneable;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ConstraintsEntity;
using tdme::engine::physics::ContactCache;
using tdme::engine::physics::DynamicVector;
using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::Matrix6x6;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;
using tdme::utils::Key;

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
typedef ::SubArray< ::tdme::engine::physics::CollisionResponse, ::java::lang::ObjectArray > CollisionResponseArray;
typedef ::SubArray< ::tdme::engine::physics::ConstraintsEntity, ::java::lang::ObjectArray > ConstraintsEntityArray;
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6, ::java::lang::ObjectArray > Matrix1x6Array;
typedef ::SubArray< ::tdme::engine::physics::Matrix6x6, ::java::lang::ObjectArray > Matrix6x6Array;
typedef ::SubArray< ::tdme::engine::physics::Vector6, ::java::lang::ObjectArray > Vector6Array;
}  // namespace physics
}  // namespace engine

namespace utils {
typedef ::SubArray< ::tdme::utils::Key, ::java::lang::ObjectArray > KeyArray;
}  // namespace utils
}  // namespace tdme

namespace  {
typedef ::SubArray< ::int32_tArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > int32_tArrayArray;
}  // namespace 

namespace tdme {
namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Matrix1x6ArrayArray;
typedef ::SubArray< ::tdme::engine::physics::Vector6Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Vector6ArrayArray;
}  // namespace physics
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using tdme::engine::physics::CollisionResponseArray;
using tdme::engine::physics::ConstraintsEntityArray;
using tdme::engine::physics::Matrix1x6Array;
using tdme::engine::physics::Matrix1x6ArrayArray;
using tdme::engine::physics::Matrix6x6Array;
using tdme::engine::physics::Vector6Array;
using tdme::engine::physics::Vector6ArrayArray;
using tdme::utils::KeyArray;

struct default_init_tag;

/** 
 * Constraints solver
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::ConstraintsSolver final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	static constexpr int32_t BODIES_MAX { 1024 };
	static constexpr int32_t CONSTRAINTS_MAX { 1024 * 3 };

private:
	int32_t constraintsEntityCount {  };
	int32_t constraintsCount {  };
	int32_t keyCount {  };
	vector<RigidBody*> rigidBodies {  };
	map<wstring, RigidBody*> constrainedBodies {  };
	ContactCache* contactCache {  };
	int32_tArrayArray* constraintsBodyIdxMap {  };
	vector<array<Matrix1x6*, 2>> jacobianMatrices {  };
	vector<array<Vector6*, 2>> bVectors {  };
	DynamicVector* lambda {  };
	DynamicVector* lambdaInit {  };
	DynamicVector* errorValues {  };
	DynamicVector* b {  };
	DynamicVector* lowerBounds {  };
	DynamicVector* upperBounds {  };
	floatArray* d {  };
	ConstraintsEntityArray* constraintsEntities {  };
	KeyArray* keys {  };
	vector<Matrix6x6*> invInertiaMatrices {  };
	vector<Vector6*> velocityVectors {  };
	vector<Vector6*> constrainedVelocityVectors {  };
	vector<Vector6*> forcesVectors {  };
	vector<Vector6*> a {  };
	vector<RigidBody*> rigidBodiesVelocityChange {  };
	vector<RigidBody*> rigidBodiesCurrentChain {  };
	vector<RigidBody*> rigidBodiesChainsResult {  };
	floatArray* tmpLamdaValues {  };
	Matrix1x6* tmpMatrix1x6 {  };
	Vector6* tmpVector6 {  };
	Vector3* newLinearVelocity {  };
	Vector3* newAngularVelocity {  };
	Vector3* force {  };
	Vector3* torque {  };
protected:

	/** 
	 * Protected constructor
	 * @param rigid bodies
	 */
	void ctor(const vector<RigidBody*>& rigidBodies);

public: /* protected */

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * @return constraints entity
	 */
	ConstraintsEntity* allocateConstraintsEntity();

	/** 
	 * @return key
	 */
	Key* allocateKey();

	/** 
	 * @return key
	 */
	void releaseKey();

private:

	/** 
	 * Init method
	 * @param delta time
	 * @param constraints
	 * @param rigid bodies
	 */
	void initialize(float dt);

	/** 
	 * Fill matrices
	 */
	void fillMatrices();

	/** 
	 * Compute vector b
	 * @param delta time
	 */
	void computeVectorB(float dt);

	/** 
	 * Computes matrix b
	 */
	void computeMatrixB();

	/** 
	 * Compute vector a
	 * @param a
	 */
	void computeVectorA();

	/** 
	 * PGLCP
	 */
	void PGLCP();

	/** 
	 * Compute vector velocity constraints
	 */
	void computeVectorVelocityConstraints(float dt);

	/** 
	 * Update contact cache
	 */
	void updateContactCache();

	/** 
	 * Finds rigid body successors in a direction for given rigid body src 
	 * @param rigid body src
	 * @param normal last
	 * @param rigid bodies current chain
	 * @param rigid bodies current chain result
	 * @param calls
	 */
	void checkChainSuccessor(RigidBody* rigidBodySrc, Vector3* normalLast, vector<RigidBody*>& rigidBodiesCurrentChain);

public: /* protected */

	/** 
	 * Process rigid body chain
	 * @param idx
	 * @param rigid bodies current chain
	 * @return new idx to process
	 */
	int32_t processRigidBodyChain(int32_t idx, const vector<RigidBody*>& rigidBodiesCurrentChain);

	/** 
	 * Check if we have any user velocity rigids
	 * which have opposite velocity and do collide directly or via other objects
	 */
	void checkVelocityConstraint();

	/** 
	 * Compute 
	 * @param delta time
	 * @param constraints
	 * @param rigid bodies
	 */
	void compute(float dt);

private:

	/** 
	 * Set constrained linear and angular velocity for given body into dest vector
	 * @param body
	 * @param dest
	 */
	void getConstrainedVelocity(RigidBody* body, Vector3* linearVelocity, Vector3* angularVelocity);

public: /* protected */

	/** 
	 * Updates all bodies 
	 * @param delta time
	 */
	void updateAllBodies(float deltaTime);

	// Generated
	ConstraintsSolver(const vector<RigidBody*>& rigidBodies);
protected:
	ConstraintsSolver(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
