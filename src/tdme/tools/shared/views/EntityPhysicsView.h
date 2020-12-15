
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/Gizmo.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::engine::prototype::Prototype;
using tdme::tools::shared::views::Gizmo;
using tdme::tools::shared::views::PopUps;

/**
 * Entity physics view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityPhysicsView final: public Gizmo
{
public:
	static constexpr int DISPLAY_BOUNDINGVOLUMEIDX_ALL { -1 };

private:
	static constexpr int MOUSE_DOWN_LAST_POSITION_NONE { -1 };

	Engine* engine { nullptr };
	EntityPhysicsSubScreenController* entityPhysicsSubScreenController { nullptr };
	PopUps* popUps { nullptr };

	int maxBoundingVolumeCount;

	int displayBoundingVolumeIdxLast;
	int mouseDownLastX;
	int mouseDownLastY;
	Vector3 totalDeltaScale;

	int displayBoundingVolumeIdx;
	bool displayBoundingVolume;

	int32_t boundingVolumeTypeMask;

public:
	/**
	 * Public constructor
	 * @param entityPhysicsSubScreenController pop ups
	 * @param popUps model editor screen controller
	 * @param maxBoundingVolumeCount maximum number of editable bounding volumes or -1 for default
	 * @param boundingVolumeTypeMask bounding volume type mask
	 */
	EntityPhysicsView(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, PopUps* popUps, int maxBoundingVolumeCount = -1, int32_t boundingVolumeTypeMask = EntityPhysicsSubScreenController::BOUNDINGVOLUMETYPE_ALL);

	/**
	 * Destructor
	 */
	~EntityPhysicsView();

	/**
	 * @return display bounding volume
	 */
	inline  bool isDisplayBoundingVolume() {
		return displayBoundingVolume;
	}

	/**
	 * Set up bounding volume visibility
	 * @param displayBoundingVolume bounding volume
	 */
	inline  void setDisplayBoundingVolume(bool displayBoundingVolume) {
		this->displayBoundingVolume = displayBoundingVolume;
	}

	/**
	 * @return bounding volume index to display or DISPLAY_BOUNDINGVOLUMEIDX_ALL
	 */
	inline int getDisplayBoundingVolumeIdx() const {
		return displayBoundingVolumeIdx;
	}

	/**
	 * Set display bounding volume idx
	 * @param displayBoundingVolumeIdx display bounding volume index or DISPLAY_BOUNDINGVOLUMEIDX_ALL
	 */
	inline void setDisplayBoundingVolumeIdx(int displayBoundingVolumeIdx) {
		this->displayBoundingVolumeIdx = displayBoundingVolumeIdx;
	}

	/**
	 * @return pop up views
	 */
	PopUps* getPopUpsViews();

	/**
	 * Init
	 */
	void initialize();

	/**
	 * Reset bounding volume
	 * @param entity entity
	 * @param idx idx
	 * @param type type
	 */
	void resetBoundingVolume(Prototype* entity, int idx, int type);

	/**
	 * Set bounding volumes
	 * @param entity entity
	 */
	void setBoundingVolumes(Prototype* entity);

	/**
	 * Unset bounding volumes
	 */
	void unsetBoundingVolumes();

	/**
	 * Select bounding volume type
	 * @param idx idx
	 * @param bvTypeId bounding volume type
	 */
	void selectBoundingVolumeType(int idx, int bvTypeId);

	/**
	 * Set terrain mesh
	 * @param entity entity
	 */
	void setTerrainMesh(Prototype* entity);

	/**
	 * Unset terrain mesh
	 */
	void unsetTerrainMesh();

	/**
	 * Set convex meshes
	 * @param entity entity
	 */
	void setConvexMeshes(Prototype* entity);

	/**
	 * Unset convex meshes
	 */
	void unsetConvexMeshes();

	/**
	 * Unset physics
	 */
	void unsetPhysics();

	/**
	 * Set physics
	 * @param entity entity
	 */
	void setPhysics(Prototype* entity);

private:

	/**
	 * Clear model bounding volume
	 * @param idx idx
	 */
	void clearModelBoundingVolume(int idx);

	/**
	 * Setup model bounding volume
	 * @param entity entity
	 * @param idx idx
	 */
	void setupModelBoundingVolume(Prototype* entity, int idx);

public:

	/**
	 * On bounding volume none apply
	 * @param entity entity
	 * @param idx bounding volume index
	 */
	void applyBoundingVolumeNone(Prototype* entity, int idx);

	/**
	 * On bounding volume sphere apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param center sphere center
	 * @param radius radius
	 */
	void applyBoundingVolumeSphere(Prototype* entity, int idx, const Vector3& center, float radius);

	/**
	 * On bounding volume capsule apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param a point a
	 * @param b point b
	 * @param radius radius
	 */
	void applyBoundingVolumeCapsule(Prototype* entity, int idx, const Vector3& a, const Vector3& b, float radius);

	/**
	 * On bounding volume AABB apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param min AABB min vector
	 * @param max AABB max vector
	 */
	void applyBoundingVolumeAabb(Prototype* entity, int idx, const Vector3& min, const Vector3& max);

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
	void applyBoundingVolumeObb(Prototype* entity, int idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/**
	 * On bounding volume convex mesh apply
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param fileName file name
	 */
	void applyBoundingVolumeConvexMesh(Prototype* entity, int idx, const string& fileName);

	/**
	 * Apply bounding volume transformations
	 * @param entity entity
	 * @param idx bounding volume index
	 * @param transformations transformations
	 * @param objectScale object scale
	 * @param guiOnly only update GUI not the BV it self
	 */
	void applyBoundingVolumeTransformations(Prototype* entity, int idx, const Transformations& transformations, const Vector3& objectScale, bool guiOnly);

	/**
	 * Handle input events
	 * @param entity entity
	 * @param objectScale object scale
	 */
	void handleInputEvents(Prototype* entity, const Vector3& objectScale);

	/**
	 * Display
	 * @param entity entity
	 */
	void display(Prototype* entity);

	/**
	 * Update GIZMO
	 * @param entity prototype
	 */
	void updateGizmo(Prototype* entity);

	/**
	 * Set GIZMO rotation
	 * @param entity prototype
	 * @param transformations transformations
	 */
	void setGizmoRotation(Prototype* entity, const Transformations& transformations);

	/**
	 * Start editing bounding volume
	 * @param entity entity
	 */
	void startEditingBoundingVolume(Prototype* entity);

	/**
	 * End editing bounding volume
	 * @param entity entity
	 */
	void endEditingBoundingVolume(Prototype* entity);

	/**
	 * @return is editing bounding volume
	 */
	bool isEditingBoundingVolume(Prototype* entity);

};
