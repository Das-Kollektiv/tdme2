#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>

using std::array;
using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;
using tdme::utilities::MutableString;

/**
 * Particle system editor tab controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController final
	: public TabController
{

private:
	BasePropertiesSubController* basePropertiesSubController { nullptr };
	PrototypeDisplaySubController* prototypeDisplaySubController { nullptr };
	PrototypePhysicsSubController* prototypePhysicsSubController { nullptr };
	PrototypeSoundsSubController* prototypeSoundsSubController { nullptr };
	PrototypeScriptSubController* prototypeScriptSubController { nullptr };
	ParticleSystemEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };

	array<string, 3> applyBaseNodes {
		"particletype_type",
		"particleemitter_type",
		"particleemitter_type_details"
	};

	array<string, 6> applyOPSNodes {
		"particletype_object_scale",
		"particletype_object_maxcount",
		"particletype_object_autoemit"
	};

	array<string, 6> applyPPSNodes {
		"particletype_point_size",
		"particletype_point_maxcount",
		"particletype_point_horizontal_sprites",
		"particletype_point_vertical_sprites",
		"particletype_point_fps",
		"particletype_point_autoemit"
	};

	array<string, 5> applyFPSNodes {
		"particletype_fog_size",
		"particletype_fog_maxcount",
		"particletype_fog_horizontal_sprites",
		"particletype_fog_vertical_sprites",
		"particletype_fog_fps",
	};

	array<string, 24> applyBBPENodes {
		"particleemitter_box_location_x",
		"particleemitter_box_location_y",
		"particleemitter_box_location_z",
		"particleemitter_box_rotation_x",
		"particleemitter_box_rotation_y",
		"particleemitter_box_rotation_z",
		"particleemitter_box_halfsize_x",
		"particleemitter_box_halfsize_y",
		"particleemitter_box_halfsize_z",
		"particleemitter_box_colorstart",
		"particleemitter_box_colorend",
		"particleemitter_box_count",
		"particleemitter_box_lifetime_min",
		"particleemitter_box_lifetime_max",
		"particleemitter_box_velocity_min_x",
		"particleemitter_box_velocity_min_y",
		"particleemitter_box_velocity_min_z",
		"particleemitter_box_velocity_max_x",
		"particleemitter_box_velocity_max_y",
		"particleemitter_box_velocity_max_z",
		"particleemitter_box_mass_min",
		"particleemitter_box_mass_max"
	};

	array<string, 14> applyPPENodes {
		"particleemitter_point_location_x",
		"particleemitter_point_location_y",
		"particleemitter_point_location_z",
		"particleemitter_point_count",
		"particleemitter_point_lifetime_min",
		"particleemitter_point_lifetime_max",
		"particleemitter_point_velocity_min_x",
		"particleemitter_point_velocity_min_y",
		"particleemitter_point_velocity_min_z",
		"particleemitter_point_velocity_max_x",
		"particleemitter_point_velocity_max_y",
		"particleemitter_point_velocity_max_z",
		"particleemitter_point_mass_min",
		"particleemitter_point_mass_max"
	};

	array<string, 15> applySPENodes {
		"particleemitter_sphere_location_x",
		"particleemitter_sphere_location_y",
		"particleemitter_sphere_location_z",
		"particleemitter_sphere_radius",
		"particleemitter_sphere_count",
		"particleemitter_sphere_lifetime_min",
		"particleemitter_sphere_lifetime_max",
		"particleemitter_sphere_velocity_min_x",
		"particleemitter_sphere_velocity_min_y",
		"particleemitter_sphere_velocity_min_z",
		"particleemitter_sphere_velocity_max_x",
		"particleemitter_sphere_velocity_max_y",
		"particleemitter_sphere_velocity_max_z",
		"particleemitter_sphere_mass_min",
		"particleemitter_sphere_mass_max"
	};

	array<string, 18> applyCPENodes {
		"particleemitter_circle_location_x",
		"particleemitter_circle_location_y",
		"particleemitter_circle_location_z",
		"particleemitter_circle_rotation_x",
		"particleemitter_circle_rotation_y",
		"particleemitter_circle_rotation_z",
		"particleemitter_circle_radius",
		"particleemitter_circle_count",
		"particleemitter_circle_lifetime_min",
		"particleemitter_circle_lifetime_max",
		"particleemitter_circle_velocity_min_x",
		"particleemitter_circle_velocity_min_y",
		"particleemitter_circle_velocity_min_z",
		"particleemitter_circle_velocity_max_x",
		"particleemitter_circle_velocity_max_y",
		"particleemitter_circle_velocity_max_z",
		"particleemitter_circle_mass_min",
		"particleemitter_circle_mass_max",
	};

	array<string, 16> applyRPENodes {
		"particleemitter_radial_location_x",
		"particleemitter_radial_location_y",
		"particleemitter_radial_location_z",
		"particleemitter_radial_rotation_x",
		"particleemitter_radial_rotation_y",
		"particleemitter_radial_rotation_z",
		"particleemitter_radial_radius",
		"particleemitter_radial_colorstart",
		"particleemitter_radial_colorend",
		"particleemitter_radial_count",
		"particleemitter_radial_lifetime_min",
		"particleemitter_radial_lifetime_max",
		"particleemitter_radial_velocity_min",
		"particleemitter_radial_velocity_max",
		"particleemitter_radial_mass_min",
		"particleemitter_radial_mass_max"
	};

public:
	/**
	 * Public constructor
	 * @param view view
	 */
	ParticleSystemEditorTabController(ParticleSystemEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~ParticleSystemEditorTabController();

	/**
	 * @return display sub screen controller
	 */
	inline PrototypeDisplaySubController* getPrototypeDisplaySubController() {
		return prototypeDisplaySubController;
	}

	/**
	 * @return pyhsics sub screen controller
	 */
	inline PrototypePhysicsSubController* getPrototypePhysicsSubController() {
		return prototypePhysicsSubController;
	}

	/**
	 * @return prototype sounds sub screen controller
	 */
	inline PrototypeSoundsSubController* getPrototypeSoundsSubController() {
		return prototypeSoundsSubController;
	}

	/**
	 * Get view
	 */
	ParticleSystemEditorTabView* getView();

	// overridden method
	GUIScreenNode* getScreenNode() override;

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void save() override;
	void saveAs() override;

	// overridden methods
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) override;

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * Set particle system details
	 * @param particleSystemIdx particle system index
	 */
	void setParticleSystemDetails(int particleSystemIdx);

	/**
	 * Apply particle system details
	 * @param particleSystemIdx particle system index
	 */
	void applyParticleSystemDetails(int particleSystemIdx);

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Update point particle system emitter
	 * @param position position
	 */
	void updatePointParticleSystemEmitter(const Vector3& position);

	/**
	 * Update bounding box particle system emitter
	 * @param center center
	 * @param axis0 axis 0
	 * @param axis1 axis 1
	 * @param axis2 axis 2
	 * @param halfExtension half extension
	 */
	void updateBoundingBoxParticleSystemEmitter(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/**
	 * Update circle particle system emitter
	 * @param center center
	 * @param axis0 axis 0
	 * @param axis1 axis 1
	 * @param axis2 axis 2
	 * @param radius radius
	 */
	void updateCircleParticleSystemEmitter(const Vector3& center, const Vector3& axis0, const Vector3& axis1, float radius);

	/**
	 * Update radial particle system emitter
	 * @param center center
	 * @param axis0 axis 0
	 * @param axis1 axis 1
	 * @param axis2 axis 2
	 * @param radius radius
	 */
	void updateRadialParticleSystemEmitter(const Vector3& center, const Vector3& axis0, const Vector3& axis1, float radius);

	/**
	 * Update sphere particle system emitter
	 * @param center center
	 * @param radius radius
	 */
	void updateSphereParticleSystemEmitter(const Vector3& center, float radius);

	/**
	 * Update info text line
	 * @param text text
	 */
	void updateInfoText(const MutableString& text);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

};
