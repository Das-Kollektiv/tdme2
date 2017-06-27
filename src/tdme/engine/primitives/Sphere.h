// Generated from /tdme/src/tdme/engine/primitives/Sphere.java

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
 * Sphere
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Sphere final
	: public virtual Object
	, public BoundingVolume
{

public:
	typedef Object super;

public: /* protected */
	Vector3* center {  };
	float radius {  };

private:
	Vector3* axis {  };

public:

	/** 
	 * Creates a sphere bounding volume
	 * @param center
	 * @param radius
	 * @return bounding volume
	 */
	static BoundingVolume* createBoundingVolume(Vector3* center, float radius);
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * you should use the new bounding volume interface when using bounding volumes
	 * and not instantiate bounding volume classes directly
	 * @param center
	 * @param radius
	 */
	void ctor(Vector3* center, float radius);

public:
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	Vector3* getCenter() override;

	/** 
	 * @return float radius
	 */
	float getRadius();
	float getSphereRadius() override;

	/** 
	 * Set up radius
	 * @param radius
	 */
	void setRadius(float radius);

	/** 
	 * Set up sphere
	 * @param center
	 * @param radius
	 * @return this sphere
	 */
	Sphere* set(Vector3* center, float radius);
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(Vector3* axis) override;
	void update() override;
	BoundingVolume* clone() override;
	String* toString() override;

	// Generated
	Sphere();
	Sphere(Vector3* center, float radius);
protected:
	Sphere(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
