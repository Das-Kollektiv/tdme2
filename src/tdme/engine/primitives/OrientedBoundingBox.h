// Generated from /tdme/src/tdme/engine/primitives/OrientedBoundingBox.java

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
using tdme::engine::primitives::BoundingBox;
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
 * Oriented Bounding Box
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::OrientedBoundingBox final
	: public virtual Object
	, public BoundingVolume
{

public:
	typedef Object super;
	static Vector3* AABB_AXIS_X;
	static Vector3* AABB_AXIS_Y;
	static Vector3* AABB_AXIS_Z;

public: /* protected */
	static int32_tArrayArray* facesVerticesIndexes;
	Vector3* center {  };
	Vector3Array* axes {  };
	Vector3* halfExtension {  };
	Vector3Array* vertices {  };
	Vector3* axis {  };
	Vector3Array* axisTransformed {  };
	Vector3* direction {  };
	Vector3* scale {  };
	float sphereRadius {  };

public:

	/** 
	 * Creates a oriented bounding box bounding volume
	 * @param center
	 * @param axis 0
	 * @param axis 1
	 * @param axis 2
	 * @param half extension
	 * @return bounding volume
	 */
	static BoundingVolume* createBoundingVolume(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension);
protected:

	/** 
	 * Public constructor
	 * you should use the new bounding volume interface when using bounding volumes
	 * and not instantiate bounding volume classes directly
	 * @param center
	 * @param axis 0
	 * @param axis 1
	 * @param axis 2
	 * @param half extension
	 */
	void ctor(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension);

	/** 
	 * Protected constructor
	 * @param bounding box
	 */
	void ctor(BoundingBox* bb);

	/** 
	 * Public constructor
	 * @param bounding box
	 */
	void ctor();

public:
	Vector3* getCenter() override;
	float getSphereRadius() override;

	/** 
	 * @return 3 axes
	 */
	Vector3Array* getAxes();

	/** 
	 * @return half extension
	 */
	Vector3* getHalfExtension();

	/** 
	 * Set up oriented bounding box from bounding box
	 * @param bb
	 */
	void fromBoundingBox(BoundingBox* bb);

	/** 
	 * Set up oriented bounding box from oriented bounding box
	 * @param bb
	 */
	void fromOrientedBoundingBox(OrientedBoundingBox* obb);
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void update() override;

	/** 
	 * @return oriented bounding box vertices
	 */
	Vector3Array* getVertices();

	/** 
	 * @return faces vertices indexes
	 */
	static int32_tArrayArray* getFacesVerticesIndexes();
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;

	/** 
	 * Computes nearest point on obb face from point in obb
	 * @param point in obb
	 * @param point on face
	 */
	void computeNearestPointOnFaceBoundingVolume(Vector3* pointInObb, Vector3* pointOnFace);

	/** 
	 * Computes nearest point on obb face from point in obb on given axis
	 * @param axis idx
	 * @param point in obb
	 * @param point on face
	 */
	void computeNearestPointOnFaceBoundingVolumeAxis(int32_t axisIdx, Vector3* pointInObb, Vector3* pointOnFace);

	/** 
	 * Computes nearest point on obb face from point in obb
	 * @param point in obb
	 * @param point on face
	 */
	void computeOppositePointOnFaceBoundingVolume(Vector3* pointInObb, Vector3* pointOnFace);

	/** 
	 * Computes nearest point on obb face from point in obb on given axis
	 * @param axis idx
	 * @param point in obb
	 * @param point on face
	 */
	void computeOppositePointOnFaceBoundingVolumeAxis(int32_t axisIdx, Vector3* pointInObb, Vector3* pointOnFace);
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(Vector3* axis) override;
	BoundingVolume* clone() override;
	String* toString() override;

	// Generated
	OrientedBoundingBox(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension);
	OrientedBoundingBox(BoundingBox* bb);
	OrientedBoundingBox();
protected:
	OrientedBoundingBox(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
