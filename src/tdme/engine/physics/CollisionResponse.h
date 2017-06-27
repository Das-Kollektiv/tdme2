// Generated from /tdme/src/tdme/engine/physics/CollisionResponse.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::physics::CollisionResponse_Entity;
using tdme::math::Vector3;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Collision response
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionResponse final
	: public Object
{

public:
	typedef Object super;
	static constexpr int32_t ENTITY_COUNT { 15 };
	static constexpr int32_t HITPOINT_COUNT { 30 };

public: /* protected */
	_ArrayList* entities {  };
	int32_t entityCount {  };
	CollisionResponse_Entity* selectedEntity {  };
protected:

	/** 
	 * Public constructor
	 * @param distance
	 * @param normal
	 */
	void ctor();

public:

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * Adds a collision response entity 
	 * @param distance
	 * @return Entity or null
	 */
	CollisionResponse_Entity* addResponse(float distance);

	/** 
	 * @return entity count
	 */
	int32_t getEntityCount();

	/** 
	 * @return selected entity
	 */
	CollisionResponse_Entity* getSelectedEntity();

	/** 
	 * Selects entity at given index
	 * @param idx
	 * @return
	 */
	CollisionResponse_Entity* getEntityAt(int32_t idx);

	/** 
	 * Selects entity at given index
	 * @param idx
	 * @return
	 */
	CollisionResponse* selectEntityAt(int32_t idx);

	/** 
	 * Select entity with least penetration but exclude given axis
	 * @param axis
	 * @param respect direction
	 * @return
	 */
	CollisionResponse* selectEntityExcludeAxis(Vector3* axis, bool respectDirection);

	/** 
	 * Select entity on given axis with least penetration
	 * @param axis
	 * @param respect direction
	 * @return
	 */
	CollisionResponse* selectEntityOnAxis(Vector3* axis, bool respectDirection);
	bool hasEntitySelected();
	float getDistance();
	bool hasPenetration();
	float getPenetration();
	Vector3* getNormal();

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

public: /* protected */

	/** 
	 * Invert normals
	 */
	void invertNormals();

public:

	/** 
	 * Set up response from given collision response
	 * @param response
	 */
	CollisionResponse* fromResponse(CollisionResponse* response);

	/** 
	 * Set up response from given collision response
	 * @param response
	 */
	CollisionResponse* mergeResponse(CollisionResponse* response);
	String* toString() override;

	// Generated
	CollisionResponse();
protected:
	CollisionResponse(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class CollisionResponse_Entity;
};
