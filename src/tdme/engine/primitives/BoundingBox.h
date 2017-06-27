// Generated from /tdme/src/tdme/engine/primitives/BoundingBox.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using java::lang::Object;
using tdme::engine::primitives::BoundingVolume;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::String;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
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
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

namespace  {
typedef ::SubArray< ::int32_tArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > int32_tArrayArray;
}  // namespace 

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Axis Aligned Bounding Box
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::BoundingBox final
	: public virtual Object
	, public BoundingVolume
{

public:
	typedef Object super;

public: /* protected */
	static int32_tArrayArray* facesVerticesIndexes;
	Vector3* min {  };
	Vector3* max {  };
	Vector3* center {  };

private:
	float sphereRadius {  };
	Vector3Array* vertices {  };
	Vector3* halfExtension {  };

public:

	/** 
	 * Creates a bounding volume bounding volume
	 * @param min
	 * @param max
	 * @return bounding volume
	 */
	static BoundingVolume* createBoundingVolume(Vector3* min, Vector3* max);
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * you should use the new bounding volume interface when using bounding volumes
	 * and not instantiate bounding volume classes directly
	 * @param bounding box
	 */
	void ctor(BoundingBox* boundingBox);

	/** 
	 * Public constructor
	 * you should use the new bounding volume interface when using bounding volumes
	 * and not instantiate bounding volume classes directly
	 * @param min vector
	 * @param max vector
	 */
	void ctor(Vector3* min, Vector3* max);

public:

	/** 
	 * @return min x,y,z vertex
	 */
	Vector3* getMin();

	/** 
	 * @return max x,y,z vertex
	 */
	Vector3* getMax();

	/** 
	 * Returns bounding box vertices
	 * @param bounding box
	 * @return vertices
	 */
	Vector3Array* getVertices();

	/** 
	 * @return faces vertices indexes
	 */
	static int32_tArrayArray* getFacesVerticesIndexes();
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
	BoundingBox();
	BoundingBox(BoundingBox* boundingBox);
	BoundingBox(Vector3* min, Vector3* max);
protected:
	BoundingBox(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
