// Generated from /tdme/src/tdme/engine/physics/CollisionResponse.java

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
using java::lang::String;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Collision Response Entity
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionResponse_Entity final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	float distance {  };
	Vector3* normal {  };
	vector<Vector3*> hitPoints {  };
	int32_t hitPointsCount {  };

public:

	/** 
	 * @return distance
	 */
	float getDistance();

	/** 
	 * Set distance
	 * @param distance
	 */
	void setDistance(float distance);

	/** 
	 * @return penetration
	 */
	float getPenetration();

	/** 
	 * @return normal
	 */
	Vector3* getNormal();

	/** 
	 * Adds a hit point
	 * @param hit point
	 */
	void addHitPoint(Vector3* hitPoint);

	/** 
	 * @return hit points count
	 */
	int32_t getHitPointsCount();

	/** 
	 * Get hit point of given index 
	 * @param i
	 * @return hit point for given hit points index
	 */
	Vector3* getHitPointAt(int32_t i);
	String* toString() override;

	// Generated
	CollisionResponse_Entity();
protected:
	CollisionResponse_Entity(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class CollisionResponse;
};
