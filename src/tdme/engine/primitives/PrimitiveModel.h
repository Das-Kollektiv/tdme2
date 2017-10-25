
#pragma once

#include <map>
#include <string>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
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
	 * Set up a convex mesh model
	 * @param model
	 */
	static void setupConvexMeshModel(Model* model);

private:
	/** 
	 * Set up convex mesh material
	 * @param groups
	 */
	static void setupConvexMeshMaterial(map<string, Group*>* groups, Material* material);

public:
	/** 
	 * Creates a model from bounding volume
	 * @param bounding box
	 * @param id
	 * @return model
	 */
	static Model* createModel(BoundingVolume* boundingVolume, const string& id);
};
