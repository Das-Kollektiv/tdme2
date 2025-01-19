#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/Gizmo.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::tools::editor::misc::Gizmo;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;

/**
 * Prototype physics view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView final: public Gizmo
{
public:
	static constexpr int DISPLAY_BOUNDINGVOLUMEIDX_ALL { -1 };

private:
	static constexpr int MOUSE_DOWN_LAST_POSITION_NONE { -1 };

	Engine* engine { nullptr };
	PrototypePhysicsSubController* prototypePhysicsSubController { nullptr };
	PopUps* popUps { nullptr };

	int maxBoundingVolumeCount;

	Vector3 totalDeltaScale;

	int displayBoundingVolumeIdx;
	bool displayBoundingVolume;

	int32_t boundingVolumeTypeMask;

	Vector3 objectScale { 0.15f, 0.15f, 0.15f };

public:
	/**
	 * Public constructor
	 * @param engine engine
	 * @param prototypePhysicsSubController pop ups
	 * @param popUps model editor screen controller
	 * @param maxBoundingVolumeCount maximum number of editable bounding volumes or -1 for default
	 * @param boundingVolumeTypeMask bounding volume type mask
	 */
	PrototypePhysicsSubView(Engine* engine, PrototypePhysicsSubController* prototypePhysicsSubController, PopUps* popUps, int maxBoundingVolumeCount = -1, int32_t boundingVolumeTypeMask = PrototypePhysicsSubController::BOUNDINGVOLUMETYPE_ALL);

	/**
	 * Destructor
	 */
	~PrototypePhysicsSubView();

	/**
	 * @returns pop ups
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * Set object scale
	 * @param objectScale object scale
	 */
	void setObjectScale(const Vector3& objectScale) {
		this->objectScale = objectScale;
	}

	/**
	 * @returns display bounding volume
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
	 * @returns bounding volume index to display or DISPLAY_BOUNDINGVOLUMEIDX_ALL
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
	 * Clear model bounding volume
	 * @param idx idx
	 */
	void clearModelBoundingVolume(int idx);

	/**
	 * Setup model bounding volume
	 * @param prototype prototype
	 * @param idx idx
	 */
	void setupModelBoundingVolume(Prototype* prototype, int idx);

	/**
	 * On bounding volume none apply
	 * @param prototype prototype
	 * @param idx bounding volume index
	 */
	void applyBoundingVolumeNone(Prototype* prototype, int idx);

	/**
	 * On bounding volume sphere apply
	 * @param prototype prototype
	 * @param idx bounding volume index
	 * @param center sphere center
	 * @param radius radius
	 */
	void applyBoundingVolumeSphere(Prototype* prototype, int idx, const Vector3& center, float radius);

	/**
	 * On bounding volume capsule apply
	 * @param prototype prototype
	 * @param idx bounding volume index
	 * @param a point a
	 * @param b point b
	 * @param radius radius
	 */
	void applyBoundingVolumeCapsule(Prototype* prototype, int idx, const Vector3& a, const Vector3& b, float radius);

	/**
	 * On bounding volume AABB apply
	 * @param prototype prototype
	 * @param idx bounding volume index
	 * @param min AABB min vector
	 * @param max AABB max vector
	 */
	void applyBoundingVolumeAabb(Prototype* prototype, int idx, const Vector3& min, const Vector3& max);

	/**
	 * On bounding volume OBB apply
	 * @param prototype prototype
	 * @param idx bounding volume index
	 * @param center OBB center
	 * @param axis0 OBB axis 0
	 * @param axis1 OBB axis 1
	 * @param axis2 OBB axis 2
	 * @param halfExtension OBB half extension
	 */
	void applyBoundingVolumeObb(Prototype* prototype, int idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/**
	 * Apply bounding volume convex mesh clear
	 * @param prototype prototype
	 * @param idx bounding volume index
	 */
	void applyBoundingVolumeConvexMeshClear(Prototype* prototype, int idx);

	/**
	 * On bounding volume convex mesh apply
	 * @param prototype prototype
	 * @param idx bounding volume index
	 * @param fileName file name
	 */
	void applyBoundingVolumeConvexMesh(Prototype* prototype, int idx, const string& fileName);

	/**
	 * Apply bounding volume transform
	 * @param prototype prototype
	 * @param idx bounding volume index
	 * @param transform transform
	 * @param guiOnly only update GUI not the BV it self
	 */
	void applyBoundingVolumeTransform(Prototype* prototype, int idx, const Transform& transform, bool guiOnly);

	/**
	 * Handle input events
	 * @param prototype prototype
	 */
	void handleInputEvents(Prototype* prototype);

	/**
	 * Display
	 * @param prototype prototype
	 */
	void display(Prototype* prototype);

	/**
	 * Update GIZMO
	 * @param prototype prototype
	 */
	void updateGizmo(Prototype* prototype);

	/**
	 * Set GIZMO rotation
	 * @param prototype prototype
	 * @param transform transform
	 */
	void setGizmoRotation(Prototype* prototype, const Transform& transform);

	/**
	 * Start editing bounding volume
	 * @param prototype prototype
	 */
	void startEditingBoundingVolume(Prototype* prototype);

	/**
	 * End editing bounding volume
	 * @param prototype prototype
	 */
	void endEditingBoundingVolume(Prototype* prototype);

	/**
	 * @returns is editing bounding volume
	 */
	bool isEditingBoundingVolume(Prototype* prototype);

};
