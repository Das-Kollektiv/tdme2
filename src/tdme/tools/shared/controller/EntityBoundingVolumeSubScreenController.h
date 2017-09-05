// Generated from /tdme/src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::wstring;

using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
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

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUINode, ::java::lang::ObjectArray > GUINodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIParentNode, GUINodeArray > GUIParentNodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIElementNode, GUIParentNodeArray > GUIElementNodeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;
using tdme::gui::nodes::GUIElementNodeArray;
using tdme::gui::nodes::GUINodeArray;
using tdme::gui::nodes::GUIParentNodeArray;

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
	static StringArray* MODEL_BOUNDINGVOLUME_IDS;

private:
	FileDialogPath* modelPath {  };
	EntityBoundingVolumeView* view {  };
	GUIElementNodeArray* boundingVolumeTypeDropDown {  };
	GUIElementNodeArray* boundingVolumeNoneApply {  };
	GUIElementNodeArray* boundingVolume {  };
	GUIElementNodeArray* boundingvolumeSphereCenter {  };
	GUIElementNodeArray* boundingvolumeSphereRadius {  };
	GUIElementNodeArray* boundingvolumeCapsuleA {  };
	GUIElementNodeArray* boundingvolumeCapsuleB {  };
	GUIElementNodeArray* boundingvolumeCapsuleRadius {  };
	GUIElementNodeArray* boundingvolumeBoundingBoxMin {  };
	GUIElementNodeArray* boundingvolumeBoundingBoxMax {  };
	GUIElementNodeArray* boundingvolumeObbCenter {  };
	GUIElementNodeArray* boundingvolumeObbHalfextension {  };
	GUIElementNodeArray* boundingvolumeObbRotationX {  };
	GUIElementNodeArray* boundingvolumeObbRotationY {  };
	GUIElementNodeArray* boundingvolumeObbRotationZ {  };
	GUIElementNodeArray* boundingvolumeConvexMeshFile {  };
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
	virtual void setupBoundingVolumeTypes(int32_t idx, StringArray* boundingVolumeTypes);

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
	virtual void setupSphere(int32_t idx, Vector3* center, float radius);

	/** 
	 * Setup capsule bounding volume
	 * @param idx
	 * @param center
	 * @param radius
	 */
	virtual void setupCapsule(int32_t idx, Vector3* a, Vector3* b, float radius);

	/** 
	 * Setup AABB bounding volume
	 * @param idx
	 * @param min
	 * @param max
	 */
	virtual void setupBoundingBox(int32_t idx, Vector3* min, Vector3* max);

	/** 
	 * Setup oriented bounding box
	 * @param idx
	 * @param center
	 * @param axis 0
	 * @param axis 1
	 * @param axis 2
	 * @param half extension
	 */
	virtual void setupOrientedBoundingBox(int32_t idx, Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension);

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
	virtual void showErrorPopUp(String* caption, String* message);

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
};
