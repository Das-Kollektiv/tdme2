// Generated from /tdme/src/tdme/tools/shared/views/EntityBoundingVolumeView.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::Engine;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::PopUps;


struct default_init_tag;

/** 
 * Entity bounding volume view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityBoundingVolumeView
	: public virtual Object
{

public:
	typedef Object super;

private:
	Engine* engine {  };
	EntityBoundingVolumeSubScreenController* modelViewerScreenController {  };
	PopUps* popUps {  };
protected:

	/** 
	 * Public constructor
	 * @param pop ups
	 * @param model viewer screen controller
	 */
	void ctor(EntityBoundingVolumeSubScreenController* modelViewerScreenController, PopUps* popUps);

public:

	/** 
	 * @return pop up views
	 */
	virtual PopUps* getPopUpsViews();

	/** 
	 * Init
	 */
	virtual void initialize();

	/** 
	 * Reset bounding volume
	 * @param entity
	 * @param idx
	 */
	virtual void resetBoundingVolume(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * Set bounding volumes
	 * @param entity
	 */
	virtual void setBoundingVolumes(LevelEditorEntity* entity);

	/** 
	 * Unset bounding volumes
	 */
	virtual void unsetBoundingVolumes();

	/** 
	 * Select bounding volume type
	 * @param idx
	 * @param bounding volume type
	 */
	virtual void selectBoundingVolumeType(int32_t idx, int32_t bvTypeId);

private:

	/** 
	 * Update model bounding volume
	 * @param entity
	 * @param idx
	 */
	void updateModelBoundingVolume(LevelEditorEntity* entity, int32_t idx);

public:

	/** 
	 * On bounding volume none apply
	 * @param entity
	 * @param bounding volume index
	 */
	virtual void applyBoundingVolumeNone(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume sphere apply
	 * @param entity
	 * @param bounding volume index
	 * @param sphere center
	 * @param radius
	 */
	virtual void applyBoundingVolumeSphere(LevelEditorEntity* entity, int32_t idx, Vector3* center, float radius);

	/** 
	 * On bounding volume capsule apply
	 * @param entity
	 * @param bounding volume index
	 * @param point a
	 * @param point b
	 * @param radius
	 */
	virtual void applyBoundingVolumeCapsule(LevelEditorEntity* entity, int32_t idx, Vector3* a, Vector3* b, float radius);

	/** 
	 * On bounding volume AABB apply
	 * @param entity
	 * @param bounding volume index
	 * @param AABB min vector
	 * @param AABB max vector
	 */
	virtual void applyBoundingVolumeAabb(LevelEditorEntity* entity, int32_t idx, Vector3* min, Vector3* max);

	/** 
	 * On bounding volume OBB apply
	 * @param entity
	 * @param bounding volume index
	 * @param OBB center
	 * @param OBB axis 0
	 * @param OBB axis 1
	 * @param OBB axis 2
	 * @param OBB half extension
	 */
	virtual void applyBoundingVolumeObb(LevelEditorEntity* entity, int32_t idx, Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension);

	/** 
	 * On bounding volume convex mesh apply
	 * @param entity
	 * @param bounding volume index
	 * @param file
	 */
	virtual void applyBoundingVolumeConvexMesh(LevelEditorEntity* entity, int32_t idx, String* file);

	// Generated
	EntityBoundingVolumeView(EntityBoundingVolumeSubScreenController* modelViewerScreenController, PopUps* popUps);
protected:
	EntityBoundingVolumeView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
