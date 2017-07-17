// Generated from /tdme/src/tdme/engine/primitives/ConvexMesh.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using std::vector;

using java::lang::Object;
using tdme::engine::primitives::BoundingVolume;
using java::lang::String;
using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::Triangle;
using tdme::math::SeparatingAxisTheorem;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::BoundingVolume, ::java::lang::ObjectArray > BoundingVolumeArray;
typedef ::SubArray< ::tdme::engine::primitives::Triangle, ::java::lang::ObjectArray, BoundingVolumeArray > TriangleArray;
}  // namespace primitives
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::primitives::BoundingVolumeArray;
using tdme::engine::primitives::TriangleArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Convex mesh collision object
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::ConvexMesh final
	: public virtual Object
	, public BoundingVolume
{

public:
	typedef Object super;

private:
	SeparatingAxisTheorem* sat {  };
	TriangleArray* triangles {  };
	Vector3* triangleEdge1 {  };
	Vector3* triangleEdge2 {  };
	Vector3* triangleEdge3 {  };
	Vector3* triangleNormal {  };

public: /* protected */
	Vector3Array* vertices {  };
	Vector3* center {  };
	Vector3* distanceVector {  };
	Vector3* closestsPoint {  };
	float sphereRadius {  };

public:

	/** 
	 * Create convex meshes from terrain model
	 * @param model
	 * @param convex meshes
	 */
	static void createTerrainConvexMeshes(Object3DModel* model, vector<ConvexMesh*>& convexMeshes);
protected:

	/** 
	 * Public constructor
	 * @param model
	 */
	void ctor(TriangleArray* triangles);

	/** 
	 * Public constructor
	 * @param model
	 */
	void ctor(Object3DModel* model);

private:

	/** 
	 * Create vertices
	 */
	void createVertices();

public:

	/** 
	 * @return triangles
	 */
	TriangleArray* getTriangles();

	/** 
	 * @return mesh vertices
	 */
	Vector3Array* getVertices();
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestsPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	Vector3* getCenter() override;
	float getSphereRadius() override;
	float computeDimensionOnAxis(Vector3* axis) override;
	void update() override;
	BoundingVolume* clone() override;
	String* toString() override;

	// Generated
	ConvexMesh(TriangleArray* triangles);
	ConvexMesh(Object3DModel* model);
protected:
	ConvexMesh(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
