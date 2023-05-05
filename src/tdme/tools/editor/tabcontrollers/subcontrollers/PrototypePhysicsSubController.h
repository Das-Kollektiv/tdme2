#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::MutableString;

/**
 * Prototype physics sub screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController final
{
	friend class PrototypePhysicsSubController_BoundingVolumeType;
	friend class PrototypePhysicsSubController_GenerateConvexMeshes;
	friend class PrototypePhysicsSubController_onBoundingVolumeConvexMeshesFile;
	friend class PrototypePhysicsSubController_onBoundingVolumeConvexMeshFile;

private:
	GUIScreenNode* screenNode { nullptr };
	EditorView* editorView { nullptr };
	TabView* tabView { nullptr };
	PrototypePhysicsSubView* view { nullptr };
	PopUps* popUps { nullptr };
	bool isModelBoundingVolumes;
	int maxBoundingVolumeCount;
	bool boundingVolumeTabActivated;
	int boundingVolumeIdxActivated;
	int boundingVolumeTypeCount;

	array<string, 7> applyPhysicsNodes = {
		"physics_bodytype",
		"physics_dynamic_mass",
		"physics_dynamic_bounciness",
		"physics_dynamic_friction",
		"physics_dynamic_inertiatensor_x",
		"physics_dynamic_inertiatensor_y",
		"physics_dynamic_inertiatensor_z",
	};

	array<string, 4> applyBoundingVolumSphereNodes = {
		"boundingvolume_sphere_x",
		"boundingvolume_sphere_y",
		"boundingvolume_sphere_z",
		"boundingvolume_sphere_radius"
	};

	array<string, 7> applyBoundingVolumCapsuleNodes = {
		"boundingvolume_capsule_a_x",
		"boundingvolume_capsule_a_y",
		"boundingvolume_capsule_a_z",
		"boundingvolume_capsule_b_x",
		"boundingvolume_capsule_b_y",
		"boundingvolume_capsule_b_z",
		"boundingvolume_capsule_radius",
	};

	array<string, 9> applyBoundingVolumOBBNodes = {
		"boundingvolume_obb_x",
		"boundingvolume_obb_y",
		"boundingvolume_obb_z",
		"boundingvolume_obb_rotation_x",
		"boundingvolume_obb_rotation_y",
		"boundingvolume_obb_rotation_z",
		"boundingvolume_obb_width",
		"boundingvolume_obb_height",
		"boundingvolume_obb_depth"
	};

	int thumbnailTextureIdx { 0 };

public:
	enum BoundingVolumeType {
		BOUNDINGVOLUMETYPE_NONE = 1,
		BOUNDINGVOLUMETYPE_SPHERE = 2,
		BOUNDINGVOLUMETYPE_CAPSULE = 4,
		BOUNDINGVOLUMETYPE_BOUNDINGBOX = 8,
		BOUNDINGVOLUMETYPE_ORIENTEDBOUNDINGBOX = 16,
		BOUNDINGVOLUMETYPE_CONVEXMESH = 32,
		BOUNDINGVOLUMETYPE_ALL = 1 + 2 + 4 +8 + 16 + 32
	};

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabView tabView
	 * @param isModelBoundingVolumes is model bounding volumes
	 * @param maxBoundingVolumeCount maximum number of editable bounding volumes or -1 for default
	 * @param boundingVolumeTypeMask bounding volume type mask
	 */
	PrototypePhysicsSubController(EditorView* editorView, TabView* tabView, bool isModelBoundingVolumes, int maxBoundingVolumeCount = -1, int32_t boundingVolumeTypeMask = BOUNDINGVOLUMETYPE_ALL);

	/**
	 * Destructor
	 */
	~PrototypePhysicsSubController();

	/**
	 * @return view
	 */
	PrototypePhysicsSubView* getView();

	/**
	 * @return screen node
	 */
	GUIScreenNode* getScreenNode();

	/**
	 * Init
	 * @param screenNode screen node
	 */
	void initialize(GUIScreenNode* screenNode);

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

	/**
	 * Create physics XML for outliner
	 * @param prototype prototype
	 * @param xml xml
	 */
	void createOutlinerPhysicsXML(Prototype* prototype, string& xml);

	/**
	 * Set physics details
	 * @param prototype prototype
	 */
	void setPhysicsDetails(Prototype* prototype);

	/**
	 * Apply physics details
	 * @param prototype prototype
	 */
	void applyPhysicsDetails(Prototype* prototype);

	/**
	 * Update details panel
	 * @param prototype prototype
	 * @param outlinerNode outliner node
	 */
	void updateDetails(Prototype* prototype, const string& outlinerNode);

	/**
	 * Set bounding volume sphere details
	 * @param center center
	 * @param radius radius
	 */
	void setBoundingVolumeSphereDetails(const Vector3& center, float radius);

	/**
	 * Set bounding volume capsule details
	 * @param a point a
	 * @param b point b
	 * @param radius radius
	 */
	void setBoundingVolumeCapsuleDetails(const Vector3& a, const Vector3& b, float radius);

	/**
	 * Set bounding volume OOB details
	 * @param center center
	 * @param axis0 axis 0
	 * @param axis1 axis 1
	 * @param axis2 axis 2
	 * @param halfExtension half extension
	 */
	void setBoundingVolumeOBBDetails(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/**
	 * Set import convex mesh from model details
	 */
	void setImportConvexMeshFromModelDetails();

	/**
	 * Set generate convex mesh from model details
	 */
	void setGenerateConvexMeshFromModelDetails();

	/**
	 * Set bounding volume details
	 * @param prototype prototype
	 * @param boundingVolumeIdx bounding volume index
	 */
	void setBoundingVolumeDetails(Prototype* prototype, int boundingVolumeIdx);

	/**
	 * Apply bounding volume sphere details
	 * @param prototype prototype
	 * @param idx bounding volume index
	 */
	void applyBoundingVolumeSphereDetails(Prototype* prototype, int idx);

	/**
	 * Apply bounding volume capsule details
	 * @param prototype prototype
	 * @param idx bounding volume index
	 */
	void applyBoundingVolumeCapsuleDetails(Prototype* prototype, int idx);

	/**
	 * Apply bounding volume obb details
	 * @param prototype prototype
	 * @param idx bounding volume index
	 */
	void applyBoundingVolumeObbDetails(Prototype* prototype, int idx);

	/**
	 * Apply bounding volume convex mesh details
	 * @param prototype prototype
	 * @param idx bounding volume index
	 */
	void applyBoundingVolumeConvexMeshDetails(Prototype* prototype, int idx);

	/**
	 * Create bounding volume
	 * @param prototype prototype
	 */
	void createBoundingVolume(Prototype* prototype);

	/**
	 * On value changed
	 * @param node node
	 * @param prototype prototype
	 * @return if this event has been handled
	 */
	bool onChange(GUIElementNode* node, Prototype* prototype);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 * @return if this event has been handled
	 */
	bool onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

	/**
	 * On context menu requested
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 * @param prototype prototype
	 */
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY, Prototype* prototype);

	/**
	 * Enable tool bar
	 */
	void enableTools();

	/*
	 * Disable tool bar
	 */
	void disableTools();

	/**
	 * Set bounding volume convex mesh file
	 * @param boundingVolumeIdx bounding volume index
	 * @param fileName file name
	 * @param prototype prototype
	 */
	void setBoundingVolumeConvexMeshFile(int boundingVolumeIdx, const string& fileName, Prototype* prototype);

	/**
	 * Import bounding volume convex mesh file
	 * @param fileName file name
	 * @param prototype prototype
	 */
	void importBoundingVolumeConvexMeshFile(const string& fileName, Prototype* prototype);

	/**
	 * Generate bounding volume convex mesh files
	 * @param fileName file name
	 * @param prototype prototype
	 */
	void generateBoundingVolumeConvexMeshFiles(const string& fileName, Prototype* prototype);

	/**
	 * On drop
	 * @param payload payload
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 * @param prototype prototype
	 */
	bool onDrop(const string& payload, int mouseX, int mouseY, Prototype* prototype);

};
