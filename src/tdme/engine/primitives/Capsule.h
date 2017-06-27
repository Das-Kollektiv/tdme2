// Generated from /tdme/src/tdme/engine/primitives/Capsule.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using java::lang::Object;
using tdme::engine::primitives::BoundingVolume;
using java::lang::String;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Capsule primitive
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Capsule final
	: public virtual Object
	, public BoundingVolume
{

public:
	typedef Object super;

public: /* protected */
	Vector3* a {  };
	Vector3* b {  };
	float radius {  };
	Vector3* center {  };
	float sphereRadius {  };

private:
	Vector3* baSub {  };
	Vector3* paSub {  };
	Vector3* side {  };
	Vector3* cpCvsP {  };

public:

	/** 
	 * Creates a capsule bounding volume
	 * @param a
	 * @param b
	 * @param radius
	 * @return bounding volume
	 */
	static BoundingVolume* createBoundingVolume(Vector3* a, Vector3* b, float radius);
protected:

	/** 
	 * Public constructor
	 * you should use the new bounding volume interface when using bounding volumes
	 * and not instantiate bounding volume classes directly
	 * @param a
	 * @param b
	 * @param radius
	 */
	void ctor(Vector3* a, Vector3* b, float radius);

public:

	/** 
	 * @return radius
	 */
	float getRadius();

	/** 
	 * Set up radius
	 * @param radius
	 */
	void setRadius(float radius);

	/** 
	 * @return line segment point a
	 */
	Vector3* getA();

	/** 
	 * @return line segment point b
	 */
	Vector3* getB();
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void update() override;
	Vector3* getCenter() override;
	float getSphereRadius() override;
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(Vector3* axis) override;
	BoundingVolume* clone() override;
	String* toString() override;

	// Generated
	Capsule(Vector3* a, Vector3* b, float radius);
protected:
	Capsule(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
