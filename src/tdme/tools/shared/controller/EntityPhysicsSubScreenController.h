#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::vector;
using std::string;

using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController_BoundingVolumeType;
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
class tdme::tools::shared::controller::EntityPhysicsSubScreenController
{
	friend class EntityPhysicsSubScreenController_BoundingVolumeType;
	friend class EntityPhysicsSubScreenController_GenerateConvexMeshes;
	friend class EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile;
	friend class EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile;

public:
	static constexpr int32_t MODEL_BOUNDINGVOLUME_COUNT { 8 };
	static vector<string> MODEL_BOUNDINGVOLUME_IDS;

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
	bool isModelBoundingVolumes;
	GUIElementNode* terrainMesh {  };
	GUIElementNode* terrainMeshApply {  };
	GUIElementNode* convexMeshesFile {  };
	GUIElementNode* convexMeshesLoad {  };
	GUIElementNode* convexMeshesResolution {  };
	GUIElementNode* convexMeshesDepth {  };
	GUIElementNode* convexMeshesConcavity {  };
	GUIElementNode* convexMeshesPlaneDownSampling {  };
	GUIElementNode* convexMeshesConvexHullDownSampling {  };
	GUIElementNode* convexMeshesAlpha {  };
	GUIElementNode* convexMeshesBeta {  };
	GUIElementNode* convexMeshesMaxVerticesPerConvexHull {  };
	GUIElementNode* convexMeshesMinVolumePerConvexHull {  };
	GUIElementNode* convexMeshesPCA {  };
	GUIElementNode* convexMeshesRemove {  };
	GUIElementNode* convexMeshesGenerate {  };
	GUIElementNode* bodyTypeDropdown {  };
	GUIElementNode* bodyTypeDropdownApply {  };
	GUIElementNode* bodyMass {  };
	GUIElementNode* bodyBounciness {  };
	GUIElementNode* bodyFriction {  };
	GUIElementNode* bodyInertiaTensor {  };
	GUIElementNode* bodyApply {  };

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
	virtual void setupBoundingVolumeTypes(int32_t idx, vector<string>* boundingVolumeTypes);

	/** 
	 * Display given bounding volume GUI elements
	 * @param bvType
	 */
	virtual void selectBoundingVolume(int32_t idx, EntityPhysicsSubScreenController_BoundingVolumeType* bvType);

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
	virtual void setupConvexMesh(int32_t idx, const string& file);

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
	 * On bounding volume convex meshes file
	 * @param entity
	 */
	virtual void onBoundingVolumeConvexMeshesFile(LevelEditorEntity* entity);

	/**
	 * On bounding volume convex meshes remove
	 * @param entity
	 */
	virtual void onBoundingVolumeConvexMeshesRemove(LevelEditorEntity* entity);

	/**
	 * On bounding volume convex meshes generate
	 * @param entity
	 */
	virtual void onBoundingVolumeConvexMeshesGenerate(LevelEditorEntity* entity);

	/**
	 * Set terrain mesh
	 * @param entity
	 */
	virtual void setTerrainMesh(LevelEditorEntity* entity);

	/**
	 * Shows the error pop up
	 * @param entity
	 */
	virtual void onSetTerrainMesh(LevelEditorEntity* entity);

	/**
	 * Unset terrain mesh
	 */
	virtual void unsetTerrainMesh();

	/**
	 * Set convex meshes
	 * @param entity
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
	 * @param entity
	 */
	virtual void setPhysics(LevelEditorEntity* entity);

	/**
	 * On physics body type apply
	 * @param entity
	 */
	virtual void onPhysicsBodyTypeApply(LevelEditorEntity* entity);

	/**
	 * On physics body apply
	 * @param entity
	 */
	virtual void onPhysicsBodyApply(LevelEditorEntity* entity);

	/**
	 * Shows the error pop up
	 */
	virtual void showErrorPopUp(const string& caption, const string& message);

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
	 * @param model editor screen controller
	 * @param is model bounding volumes
	 */
	EntityPhysicsSubScreenController(PopUps* popUps, FileDialogPath* modelPath, bool isModelBoundingVolumes);

	/**
	 * Destructor
	 */
	virtual ~EntityPhysicsSubScreenController();
};
