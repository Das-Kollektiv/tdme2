#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::array;

using tdme::engine::model::Node;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Gizmo tool for views
 * @author Andreas Drewke
 */
class tdme::tools::editor::misc::Gizmo
{
public:
	static constexpr float GIZMO_ORTHO_DEFAULT_SCALE { 150.0f };
	static constexpr float GIZMO_ORTHO_DEFAULT_Z { -200.0f };

	enum GizmoAxisIdx {
		GIZMOAXISIDX_NONE = -1,
		GIZMOAXISIDX_X = 0,
		GIZMOAXISIDX_Y = 1,
		GIZMOAXISIDX_Z = 2
	};
	enum GizmoType {
		GIZMOTYPE_NONE = 0,
		GIZMOTYPE_TRANSLATE = 1,
		GIZMOTYPE_ROTATE = 2,
		GIZMOTYPE_SCALE = 4,
		GIZMOTYPE_ALL = 8,
	};
	enum GizmoMode {
		GIZMOMODE_NONE,
		GIZMOMODE_TRANSLATE_X,
		GIZMOMODE_TRANSLATE_Y,
		GIZMOMODE_TRANSLATE_Z,
		GIZMOMODE_TRANSLATEPLANE_X,
		GIZMOMODE_TRANSLATEPLANE_Y,
		GIZMOMODE_TRANSLATEPLANE_Z,
		GIZMOMODE_SCALE_X,
		GIZMOMODE_SCALE_Y,
		GIZMOMODE_SCALE_Z,
		GIZMOMODE_SCALEPLANE_X,
		GIZMOMODE_SCALEPLANE_Y,
		GIZMOMODE_SCALEPLANE_Z,
		GIZMOMODE_ROTATE_X,
		GIZMOMODE_ROTATE_Y,
		GIZMOMODE_ROTATE_Z
	};

private:
	Engine* engine { nullptr };
	string id;
	int32_t gizmoTypeMask;
	GizmoType gizmoType;
	GizmoMode gizmoMode;
	Matrix4x4 rotationsMatrix;
	Vector3 gizmoTranslation;
	array<bool, 3> gizmoTranslationHandleDiffAvailable;
	array<Vector3, 3> gizmoTranslationHandleDiff;
	array<bool, 3> gizmoTranslationLastResultAvailable;
	array<Vector3, 3> gizmoTranslationLastResult;
	bool gizmoRotationLastResultAvailable;
	Vector3 gizmoRotationLastResult;
	Vector3 orthogonalGizmoTranslation;

	/**
	 * Compute orthogonal gizmo coordinate
	 * @param worldCoordinate world coordinate to compute
	 * @return orthogonal gizmo coordinate
	 */
	inline Vector3 computeOrthogonalGizmoCoordinate(const Vector3& worldCoordinate) {
		Vector4 orthogonalGizmoCoordinateNDC = engine->getCamera()->getModelViewProjectionMatrix().multiply(Vector4(worldCoordinate, 1.0f));
		orthogonalGizmoCoordinateNDC.scale(1.0f / orthogonalGizmoCoordinateNDC.getW());
		Vector3 orthogonalGizmoCoordinate;
		orthogonalGizmoCoordinate.setX(orthogonalGizmoCoordinateNDC.getX() * (engine->getWidth() * 0.5f));
		orthogonalGizmoCoordinate.setY(orthogonalGizmoCoordinateNDC.getY() * (engine->getHeight() * 0.5f));
		orthogonalGizmoCoordinate.setZ(GIZMO_ORTHO_DEFAULT_Z);
		return orthogonalGizmoCoordinate;
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(Gizmo)

	/**
	 * Public constructor
	 * @param engine engine
	 * @param id id
	 * @param gizmoTypeMask gizmo type mask
	 */
	Gizmo(Engine* engine, const string& id, int32_t gizmoTypeMask = GIZMOTYPE_TRANSLATE | GIZMOTYPE_ROTATE | GIZMOTYPE_SCALE);

	/**
	 * Destructor
	 */
	virtual ~Gizmo();

	/**
	 * Set engine
	 * @param engine engine
	 */
	inline void setEngine(Engine* engine) {
		this->engine = engine;
	}

	/**
	 * @return GIZMO type mask
	 */
	inline int32_t getGizmoTypeMask() const {
		return gizmoTypeMask;
	}

	/**
	 * Set GIZMO type mask
	 * @param gizmoTypeMask GIZMO type mask
	 */
	inline void setGizmoTypeMask(int gizmoTypeMask) {
		this->gizmoTypeMask = gizmoTypeMask;
		if ((gizmoType & gizmoTypeMask) == 0) gizmoType = GIZMOTYPE_ALL;
	}

	/**
	 * @return GIZMO type
	 */
	inline GizmoType getGizmoType() const {
		return gizmoType;
	}

	/**
	 * Set GIZMO type
	 * @param gizmoType GIZMO type
	 */
	inline void setGizmoType(GizmoType gizmoType) {
		if (gizmoType != GIZMOTYPE_ALL && (gizmoType & gizmoTypeMask) == 0) return;
		this->gizmoType = gizmoType;
	}

	/**
	 * @return GIZMO mode
	 */
	inline GizmoMode getGizmoMode() const {
		return gizmoMode;
	}

	/**
	 * Set GIZMO mode
	 * @param gizmoMode gizmo mode
	 */
	inline void setGizmoMode(GizmoMode gizmoMode) {
		//
		if (this->gizmoMode == gizmoMode) return;
		//
		this->gizmoMode = gizmoMode;
		//
		gizmoTranslationHandleDiffAvailable[0] = false;
		gizmoTranslationHandleDiffAvailable[1] = false;
		gizmoTranslationHandleDiffAvailable[2] = false;
		gizmoTranslationLastResultAvailable[0] = false;
		gizmoTranslationLastResultAvailable[1] = false;
		gizmoTranslationLastResultAvailable[2] = false;
		gizmoRotationLastResultAvailable = false;
	}

	/**
	 * Update gizmo
	 * @param gizmoTranslation GIZMO translation
	 * @param transformations transformations used for rotation
	 */
	void updateGizmo(const Vector3& gizmoTranslation, const Transform& transform);

	/**
	 * @return GIZMO object
	 */
	Object* getGizmoObject();

	/**
	 * Remove gizmo
	 */
	void removeGizmo();

	/**
	 * Determine gizmo movement
	 * @param mouseX current mouse X position
	 * @param mouseY current mouse Y position
	 * @param mouseDeltaPosition mouse delta position
	 * @param axisIdx vector axis index
	 * @param axis axis to check movement on
	  * @param deltaMovement delta movement result
	 * @return success
	 */
	bool determineGizmoMovement(int mouseX, int mouseY, int axisIdx, const Vector3& axis, Vector3& deltaMovement);

	/**
	 * Determine gizmo scale
	 * @param mouseX current mouse X position
	 * @param mouseY current mouse Y position
	 * @param axisIdx vector axis index
	 * @param axis axis to check movement on
	 * @param deltaScale delta scale result
	 * @return success
	 */
	bool determineGizmoScale(int mouseX, int mouseY, int axisIdx, const Vector3& axis, Vector3& deltaScale);

	/**
	 * Determine rotation on a plane given by 4 vertices
	 * @param mouseX current mouse X position
	 * @param mouseY current mouse Y position
	 * @param vertices 4 vertices that span a plane
	 * @param planeNormal plane normal to test rotation against
	 * @param deltaRotation delta rotation result
	 * @return success
	 */
	bool determineGizmoRotation(int mouseX, int mouseY, const array<Vector3, 4>& vertices, const Vector3& planeNormal, float& deltaRotation);

	/**
	 * Determine GIZMO delta transform
	 * @param mouseX mouse X position
	 * @param mouseY mouse Y position
	 * @param deltaTranslation determined delta translation
	 * @param deltaRotation determined delta rotations
	 * @param deltaScale determined delta scale
	 */
	bool determineGizmoDeltaTransformations(int mouseX, int mouseY, Vector3& deltaTranslation, Vector3& deltaRotation, Vector3& deltaScale);

	/**
	 * Select GIZMO mode
	 * @param selectedEntity selected entity
	 * @param selectedEntityNode selected entity node
	 */
	bool determineGizmoMode(Entity* selectedEntity, Node* selectedEntityNode);

	/**
	 * @return gizmo translation
	 */
	inline Vector3 getGizmoTranslation() {
		return gizmoTranslation;
	}

	/**
	 * Set gizmo rotation
	 * @param transform transform containing rotations
	 */
	void setGizmoRotation(const Transform& transform);

};
