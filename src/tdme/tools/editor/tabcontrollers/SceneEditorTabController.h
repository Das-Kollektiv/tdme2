#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/Transformations.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::engine::prototype::Prototype_Type;
using tdme::engine::Transformations;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabviews::SceneEditorTabView;
using tdme::utilities::MutableString;

/**
 * Scene editor screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabcontrollers::SceneEditorTabController final
	: public TabController
{

private:
	BasePropertiesSubController* basePropertiesSubController { nullptr };
	SceneEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };
	FileDialogPath modelPath;

	array<string, 3> applyBaseNodes = {
		"base_name",
		"base_description",
	};
	array<string, 3> applyTranslationNodes = {
		"transformation_translation_x",
		"transformation_translation_y",
		"transformation_translation_z"
	};
	array<string, 3> applyRotationNodes = {
		"transformation_rotation_x",
		"transformation_rotation_y",
		"transformation_rotation_z"
	};
	array<string, 3> applyScaleNodes = {
		"transformation_scale_x",
		"transformation_scale_y",
		"transformation_scale_z"
	};
	array<string, 3> applySkyNodes = {
		"sky_model_scale"
	};

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

	/**
	 * @return model path
	 */
	FileDialogPath* getModelPath();

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void save() override;
	void saveAs() override;
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) override;

	/**
	 * Set sky details
	 */
	void setSkyDetails();

	/**
	 * Set entity details
	 * @param entity id
	 */
	void setEntityDetails(const string& entityId);

	/**
	 * Set entity details for multiple entity selection
	 * @param pivot pivot
	 */
	void setEntityDetailsMultiple(const Vector3& pivot);

	/**
	 * Update entity details
	 * @param transformations transformations
	 */
	void updateEntityDetails(const Transformations& transformations);

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
		if (prototypeType == Prototype_Type::ENVIRONMENTMAPPING) return "tdme.png"; else // TODO: tepilogic
		if (prototypeType == Prototype_Type::MODEL) return "mesh.png"; else
		if (prototypeType == Prototype_Type::PARTICLESYSTEM) return "particle.png"; else
		if (prototypeType == Prototype_Type::TERRAIN) return "terrain.png"; else
		if (prototypeType == Prototype_Type::TRIGGER) return "tdme.png"; else return ""; // TODO: tepilogic
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
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

};
