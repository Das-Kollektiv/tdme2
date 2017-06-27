// Generated from /tdme/src/tdme/engine/primitives/Triangle.java

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
 * Triangle primitive
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Triangle final
	: public virtual Object
	, public BoundingVolume
{

public:
	typedef Object super;

public: /* protected */
	Vector3Array* vertices {  };
	Vector3* center {  };
	Vector3* closestPoint {  };
	Vector3* distanceVector {  };
	float sphereRadius {  };

private:
	Vector3* edge0 {  };
	Vector3* edge1 {  };
	Vector3* v0Point {  };

public:

	/** 
	 * Creates a triangle bounding volume
	 * @param vertex 0
	 * @param vertex 1
	 * @param vertex 2
	 * @return bounding volume
	 */
	static BoundingVolume* createBoundingVolume(Vector3* vertex0, Vector3* vertex1, Vector3* vertex2);
protected:

	/** 
	 * Public constructor
	 * you should use the new bounding volume interface when using bounding volumes
	 * and not instantiate bounding volume classes directly
	 * @param vertices
	 */
	void ctor(Vector3* vertex0, Vector3* vertex1, Vector3* vertex2);

public:

	/** 
	 * @return triangle vertices
	 */
	Vector3Array* getVertices();
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	Vector3* getCenter() override;
	float getSphereRadius() override;
	float computeDimensionOnAxis(Vector3* axis) override;
	void update() override;
	BoundingVolume* clone() override;
	String* toString() override;

	// Generated
	Triangle(Vector3* vertex0, Vector3* vertex1, Vector3* vertex2);
protected:
	Triangle(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
