// Generated from /tdme/src/tdme/engine/primitives/PrimitiveModel.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Class to create primitives model
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::PrimitiveModel final
	: public Object
{

public:
	typedef Object super;

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
	static Model* createBoundingBoxModel(BoundingBox* boundingBox, String* id);

	/** 
	 * Creates a model from oriented bounding box
	 * @param bounding box
	 * @param id
	 * @return model
	 */
	static Model* createOrientedBoundingBoxModel(OrientedBoundingBox* orientedBoundingBox, String* id);

	/** 
	 * Creates a model from oriented bounding box
	 * @param sphere
	 * @param id
	 * @param number of x segments
	 * @param number of y segments
	 * @return model
	 */
	static Model* createSphereModel(Sphere* sphere, String* id, int32_t segmentsX, int32_t segmentsY);

	/** 
	 * Creates a model from capsule
	 * @param sphere
	 * @param id
	 * @param number of x segments
	 * @param number of y segments
	 * @return model
	 */
	static Model* createCapsuleModel(Capsule* capsule, String* id, int32_t segmentsX, int32_t segmentsY);

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
	static void setupConvexMeshMaterial(_HashMap* groups, Material* material);

public:

	/** 
	 * Creates a model from bounding volume
	 * @param bounding box
	 * @param id
	 * @return model
	 */
	static Model* createModel(BoundingVolume* boundingVolume, String* id);

	// Generated
	PrimitiveModel();
protected:
	PrimitiveModel(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
