
#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::vector;
using std::wstring;

using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

/** 
 * Entity bounding volume sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController
{
	friend class EntityBoundingVolumeSubScreenController_BoundingVolumeType;
	friend class EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1;

public:
	static constexpr int32_t MODEL_BOUNDINGVOLUME_COUNT { 8 };
	static vector<wstring> MODEL_BOUNDINGVOLUME_IDS;

private:
	FileDialogPath* modelPath {  };
	EntityBoundingVolumeView* view {  };
	array<GUIElementNode*, 8> boundingVolumeTypeDropDown {  };
	array<GUIElementNode*, 8> boundingVolumeNoneApply {  };
	array<GUIElementNode*, 8> boundingVolume {  };
	array<GUIElementNode*, 8> boundingvolumeSphereCenter {  };
	array<GUIElementNode*, 8> boundingvolumeSphereRadius {  };
	array<GUIElementNode*, 8> boundingvolumeCapsuleA {  };
	array<GUIElementNode*, 8> boundingvolumeCapsuleB {  };
	array<GUIElementNode*, 8> boundingvolumeCapsuleRadius {  };
	array<GUIElementNode*, 8> boundingvolumeBoundingBoxMin {  };
	array<GUIElementNode*, 8> boundingvolumeBoundingBoxMax {  };
	array<GUIElementNode*, 8> boundingvolumeObbCenter {  };
	array<GUIElementNode*, 8> boundingvolumeObbHalfextension {  };
	array<GUIElementNode*, 8> boundingvolumeObbRotationX {  };
	array<GUIElementNode*, 8> boundingvolumeObbRotationY {  };
	array<GUIElementNode*, 8> boundingvolumeObbRotationZ {  };
	array<GUIElementNode*, 8> boundingvolumeConvexMeshFile {  };
	MutableString* value {  };

public:

	/** 
	 * @return view
	 */
	virtual EntityBoundingVolumeView* getView();

	/** 
	 * Init
	 * @param screen node
	 */
	virtual void initialize(GUIScreenNode* screenNode);

	/** 
	 * Disable bounding volume
	 */
	virtual void disableBoundingVolume(int32_t idx);

	/** 
	 * Enable bounding volume
	 * @param idx
	 */
	virtual void enableBoundingVolume(int32_t idx);

	/** 
	 * Set up model bounding volume type
	 * @param entity
	 * @param idx
	 */
	virtual void setupModelBoundingVolumeType(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * Set up bounding volume types
	 * @param idx
	 * @param bounding volume types
	 */
	virtual void setupBoundingVolumeTypes(int32_t idx, vector<wstring>* boundingVolumeTypes);

	/** 
	 * Display given bounding volume GUI elements
	 * @param bvType
	 */
	virtual void selectBoundingVolume(int32_t idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType* bvType);

	/** 
	 * Setup sphere bounding volume
	 * @param idx
	 * @param center
	 * @param radius
	 */
	virtual void setupSphere(int32_t idx, const Vector3& center, float radius);

	/** 
	 * Setup capsule bounding volume
	 * @param idx
	 * @param center
	 * @param radius
	 */
	virtual void setupCapsule(int32_t idx, const Vector3& a, const Vector3& b, float radius);

	/** 
	 * Setup AABB bounding volume
	 * @param idx
	 * @param min
	 * @param max
	 */
	virtual void setupBoundingBox(int32_t idx, const Vector3& min, const Vector3& max);

	/** 
	 * Setup oriented bounding box
	 * @param idx
	 * @param center
	 * @param axis 0
	 * @param axis 1
	 * @param axis 2
	 * @param half extension
	 */
	virtual void setupOrientedBoundingBox(int32_t idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/** 
	 * Setup convex mesh bounding volume
	 * @param idx
	 * @param file
	 */
	virtual void setupConvexMesh(int32_t idx, const wstring& file);

	/** 
	 * On pivot apply
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeTypeApply(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume none apply
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeNoneApply(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume sphere apply
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeSphereApply(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume capsule apply
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeCapsuleApply(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume AABB apply
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeAabbApply(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume OBB apply
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeObbApply(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume convex mesh apply
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeConvexMeshApply(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * On bounding volume convex mesh file clicked
	 * @param entity
	 * @param idx
	 */
	virtual void onBoundingVolumeConvexMeshFile(LevelEditorEntity* entity, int32_t idx);

	/** 
	 * Shows the error pop up
	 */
	virtual void showErrorPopUp(const wstring& caption, const wstring& message);

	/** 
	 * On action performed
	 * @param type
	 * @param node
	 * @param entity
	 */
	virtual void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node, LevelEditorEntity* entity);

	/**
	 * Public constructor
	 * @param pop ups
	 * @param model viewer screen controller
	 */
	EntityBoundingVolumeSubScreenController(PopUps* popUps, FileDialogPath* modelPath);

	/**
	 * Destructor
	 */
	virtual ~EntityBoundingVolumeSubScreenController();
};
