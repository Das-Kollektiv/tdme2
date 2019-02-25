
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using std::string;

using tdme::engine::Engine;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::PopUps;

/** 
 * Entity physics view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityPhysicsView
{
private:
	Engine* engine {  };
	EntityPhysicsSubScreenController* entityPhysicsSubScreenController {  };
	PopUps* popUps {  };

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
	 * @param entity entity
	 * @param idx idx
	 */
	virtual void resetBoundingVolume(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * Set bounding volumes
	 * @param entity entity
	 */
	virtual void setBoundingVolumes(LevelEditorEntity* entity);

	/** 
	 * Unset bounding volumes
	 */
	virtual void unsetBoundingVolumes();

	/** 
	 * Select bounding volume type
	 * @param idx idx
	 * @param bvTypeId bounding volume type
	 */
	virtual void selectBoundingVolumeType(int32_t idx, int32_t bvTypeId);

	/**
	 * Set terrain mesh
	 * @param entity entity
	 */
	virtual void setTerrainMesh(LevelEditorEntity* entity);

	/**
	 * Unset terrain mesh
	 */
	virtual void unsetTerrainMesh();

	/**
	 * Set convex meshes
	 * @param entity entity
	 */
	virtual void setConvexMeshes(LevelEditorEntity* entity);

	/**
	 * Unset convex meshes
	 */
	virtual void unsetConvexMeshes();

	/**
	 * Unset physics
	 */
	virtual void unsetPhysics();

	/**
	 * Set physics
	 * @param entity entity
	 */
	virtual void setPhysics(LevelEditorEntity* entity);

private:

	/**
	 * Clear model bounding volume
	 * @param idx idx
	 */
	void clearModelBoundingVolume(int32_t idx);

	/** 
	 * Setup model bounding volume
	 * @param entity entity
	 * @param idx idx
	 */
	void setupModelBoundingVolume(LevelEditorEntity* entity, int32_t idx);

public:

	/** 
	 * On bounding volume none apply
	 * @param entity entity
	 * @param idx bounding volume index
	 */
	virtual void applyBoundingVolumeNone(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume sphere apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param center sphere center
	 * @param radius radius
	 */
	virtual void applyBoundingVolumeSphere(LevelEditorEntity* entity, int32_t idx, const Vector3& center, float radius);

	/** 
	 * On bounding volume capsule apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param a point a
	 * @param b point b
	 * @param radius radius
	 */
	virtual void applyBoundingVolumeCapsule(LevelEditorEntity* entity, int32_t idx, const Vector3& a, const Vector3& b, float radius);

	/** 
	 * On bounding volume AABB apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param min AABB min vector
	 * @param max AABB max vector
	 */
	virtual void applyBoundingVolumeAabb(LevelEditorEntity* entity, int32_t idx, const Vector3& min, const Vector3& max);

	/** 
	 * On bounding volume OBB apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param center OBB center
	 * @param axis0 OBB axis 0
	 * @param axis1 OBB axis 1
	 * @param axis2 OBB axis 2
	 * @param halfExtension OBB half extension
	 */
	virtual void applyBoundingVolumeObb(LevelEditorEntity* entity, int32_t idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/** 
	 * On bounding volume convex mesh apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param fileName file name
	 */
	virtual void applyBoundingVolumeConvexMesh(LevelEditorEntity* entity, int32_t idx, const string& fileName);

	/**
	 * Public constructor
	 * @param entityPhysicsSubScreenController pop ups
	 * @param popUps model editor screen controller
	 */
	EntityPhysicsView(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, PopUps* popUps);
};
