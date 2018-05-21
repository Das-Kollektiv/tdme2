#pragma once

#include <map>
#include <string>

#include <ext/reactphysics3d/src/mathematics/Vector3.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;

using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Group;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;

/** 
 * Class to create primitives model
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::PrimitiveModel final
{
private:
	static constexpr int32_t SPHERE_SEGMENTS_X { 20 };
	static constexpr int32_t SPHERE_SEGMENTS_Y { 20 };
	static constexpr int32_t CAPSULE_SEGMENTS_X { 20 };
	static constexpr int32_t CAPSULE_SEGMENTS_Y { 20 };

	/**
	 * Converts a TDME2 vector to ReactPhysics3D vector
	 * @param tdme vector
	 * @returns reactphysics3d vector
	 */
	inline static reactphysics3d::Vector3 toRP3DVector3(const Vector3& vector) {
		return reactphysics3d::Vector3(vector.getX(), vector.getY(), vector.getZ());
	}

	/**
	 * Transforms a given ReactPhysics3D vector with bounding volume transform
	 * @param bounding volume
	 * @param vector
	 * @return transformed vector
	 */
	inline static Vector3 transformVector3(BoundingVolume* boundingVolume, const reactphysics3d::Vector3& vector) {
		auto vectorTransformed = boundingVolume->collisionShapeTransform * (vector * boundingVolume->collisionShape->getLocalScaling());
		return Vector3(vectorTransformed.x, vectorTransformed.y, vectorTransformed.z);
	}

	/**
	 * Transforms a given ReactPhysics3D vector with bounding volume transform
	 * @param bounding volume
	 * @param vector
	 * @return transformed vector
	 */
	inline static Vector3 transformVector3Normal(BoundingVolume* boundingVolume, const reactphysics3d::Vector3& normal) {
		auto normalTransformed = boundingVolume->collisionShapeTransform.getOrientation() * normal;
		return Vector3(normalTransformed.x, normalTransformed.y, normalTransformed.z);
	}

	/**
	 * Set up convex mesh material
	 * @param groups
	 */
	static void setupConvexMeshMaterial(map<string, Group*>* groups, Material* material);

public:
	/** 
	 * Creates a model from bounding box
	 * @param bounding box
	 * @param id
	 * @return model
	 */
	static Model* createBoundingBoxModel(BoundingBox* boundingBox, const string& id);

	/** 
	 * Creates a model from oriented bounding box
	 * @param bounding box
	 * @param id
	 * @return model
	 */
	static Model* createOrientedBoundingBoxModel(OrientedBoundingBox* orientedBoundingBox, const string& id);

	/** 
	 * Creates a model from oriented bounding box
	 * @param sphere
	 * @param id
	 * @param number of x segments
	 * @param number of y segments
	 * @return model
	 */
	static Model* createSphereModel(Sphere* sphere, const string& id, int32_t segmentsX, int32_t segmentsY);

	/** 
	 * Creates a model from capsule
	 * @param sphere
	 * @param id
	 * @param number of x segments
	 * @param number of y segments
	 * @return model
	 */
	static Model* createCapsuleModel(Capsule* capsule, const string& id, int32_t segmentsX, int32_t segmentsY);

	/** 
	 * Creates a model from convex mesh
	 * @param convex mesh
	 * @param id
	 * @return model
	 */
	static Model* createConvexMeshModel(ConvexMesh* mesh, const string& id);

	/**
	 * Set up a convex mesh model
	 * @param model
	 */
	static void setupConvexMeshModel(Model* model);

public:
	/** 
	 * Creates a model from bounding volume
	 * @param bounding volume
	 * @param id
	 * @return model
	 */
	static Model* createModel(BoundingBox* boundingVolume, const string& id);

	/**
	 * Creates a model from bounding volume
	 * @param bounding box
	 * @param id
	 * @return model
	 */
	static Model* createModel(BoundingVolume* boundingVolume, const string& id);
};
