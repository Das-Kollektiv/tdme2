#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/Transform.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::engine::prototype::Prototype_Type;
using tdme::engine::Transform;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::SceneEditorTabView;
using tdme::utilities::MutableString;

/**
 * Scene editor tab controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::SceneEditorTabController final
	: public TabController
{

private:
	BasePropertiesSubController* basePropertiesSubController { nullptr };
	SceneEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };

	array<string, 2> applyBaseNodes = {
		"base_name",
		"base_description",
	};
	array<string, 3> applyTranslationNodes = {
		"transform_translation_x",
		"transform_translation_y",
		"transform_translation_z"
	};
	array<string, 3> applyRotationNodes = {
		"transform_rotation_x",
		"transform_rotation_y",
		"transform_rotation_z"
	};
	array<string, 3> applyScaleNodes = {
		"transform_scale_x",
		"transform_scale_y",
		"transform_scale_z"
	};
	array<string, 1> applySkyNodes = {
		"sky_model_scale"
	};
	array<string, 1> applyReflectionEnvironmentMappingNodes = {
		"reflection_environmentmap"
	};
	array<string, 30> applyLightNodes = {
		"light_type",
		"light_ambient_ambient",
		"light_ambient_diffuse",
		"light_ambient_specular",
		"light_ambient_constant_attenuation",
		"light_ambient_linear_attenuation",
		"light_ambient_quadratic_attenuation",
		"light_spot_ambient",
		"light_spot_diffuse",
		"light_spot_specular",
		"light_spot_constant_attenuation",
		"light_spot_linear_attenuation",
		"light_spot_quadratic_attenuation",
		"light_spot_position_x",
		"light_spot_position_y",
		"light_spot_position_z",
		"light_spot_direction_x",
		"light_spot_direction_y",
		"light_spot_direction_z",
		"light_spot_cutoff",
		"light_spot_exponent",
		"light_directional_ambient",
		"light_directional_diffuse",
		"light_directional_specular",
		"light_directional_constant_attenuation",
		"light_directional_linear_attenuation",
		"light_directional_quadratic_attenuation",
		"light_directional_direction_x",
		"light_directional_direction_y",
		"light_directional_direction_z"
	};

	string renameEntityName;

public:
	/**
	 * Public constructor
	 * @param view view
	 */
	SceneEditorTabController(SceneEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~SceneEditorTabController();

	/**
	 * Get view
	 */
	SceneEditorTabView* getView();

	// overridden method
	GUIScreenNode* getScreenNode() override;

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) override;
	void executeCommand(TabControllerCommand command) override;

	/**
	 * Set sky details
	 */
	void setSkyDetails();

	/**
	 * Set light details
	 * @param lightIdx light index
	 */
	void setLightDetails(int lightIdx);

	/**
	 * Update light details
	 * @param lightIdx light index
	 */
	void updateLightDetails(int lightIdx);

	/**
	 * Apply light
	 * @param lightIdx light index
	 */
	void applyLightDetails(int lightIdx);

	/**
	 * Set prototype details
	 */
	void setPrototypeDetails();

	/**
	 * Update reflection details drop down
	 * @param selectedReflectionEnvironmentMappingId selected reflection environment mapping id
	 * @param mixed mixed
	 */
	void updateReflectionEnvironmentMappingDetailsDropDown(const string& selectedReflectionEnvironmentMappingId);

	/**
	 * Set entity details
	 * @param entity id
	 */
	void setEntityDetails(const string& entityId);

	/**
	 * Set entity details for multiple entity selection
	 * @param pivot pivot
	 * @param selectedReflectionEnvironmentMappingId selected reflection environment mapping id
	 */
	void setEntityDetailsMultiple(const Vector3& pivot, const string& selectedReflectionEnvironmentMappingId);

	/**
	 * Update entity details
	 * @param transform transform
	 */
	void updateEntityDetails(const Transform& transform);

	/**
	 * Update entity details
	 * @param translation translation
	 * @param rotation rotation
	 * @param scale scale
	 */
	void updateEntityDetails(const Vector3& translation, const Vector3& rotation, const Vector3& scale);

	/**
	 * Get prototype icon
	 * @param prototypeType prototype type
	 */
	inline const string getPrototypeIcon(Prototype_Type* prototypeType) {
		if (prototypeType == Prototype_Type::EMPTY) return "empty.png"; else
		if (prototypeType == Prototype_Type::ENVIRONMENTMAPPING) return "reflection.png"; else
		if (prototypeType == Prototype_Type::MODEL) return "mesh.png"; else
		if (prototypeType == Prototype_Type::PARTICLESYSTEM) return "particle.png"; else
		if (prototypeType == Prototype_Type::TERRAIN) return "terrain.png"; else
		if (prototypeType == Prototype_Type::TRIGGER) return "trigger.png"; else return "";
	}

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * Set details content
	 */
	void setDetailsContent();

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Unselect entities
	 */
	void unselectEntities();

	/**
	 * Unselect entity
	 * @param entityId entity id
	 */
	void unselectEntity(const string& entityId);

	/**
	 * Select entity
	 * @param entityId entity id
	 */
	void selectEntity(const string& entityId);

	/**
	 * Select exactly given entities
	 * @param selectedOutlinerEntityIds selected entity outliner ids
	 */
	void selectEntities(const vector<string>& selectedOutlinerEntityIds);

	/**
	 * On replace prototype
	 */
	void onReplacePrototype();

	/**
	 * Rename entity
	 * @param entityName entity name
	 */
	void startRenameEntity(const string& entityName);

	/**
	 * Rename entity
	 */
	void renameEntity();

	/**
	 * Save
	 * @param pathName path name
	 * @param fileName file name
	 */
	void save(const string& pathName, const string& fileName);

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
