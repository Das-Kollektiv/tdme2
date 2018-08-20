#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::views::EntityBaseView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

/** 
 * Entity base sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::EntityBaseSubScreenController
{
private:
	static MutableString TEXT_EMPTY;
	EntityBaseView* view {  };
	PopUps* popUps {  };
	GUIElementNode* entityName {  };
	GUIElementNode* entityDescription {  };
	GUIElementNode* entityApply {  };
	GUIElementNode* entityPropertyName {  };
	GUIElementNode* entityPropertyValue {  };
	GUIElementNode* entityPropertySave {  };
	GUIElementNode* entityPropertyAdd {  };
	GUIElementNode* entityPropertyRemove {  };
	GUIElementNode* entityPropertiesList {  };
	GUIElementNode* entityPropertyPresetApply {  };
	GUIElementNode* entityPropertiesPresets {  };
	Action* onSetEntityDataAction {  };
	MutableString* value {  };

public:

	/** 
	 * Init
	 * @param screen node
	 */
	virtual void initialize(GUIScreenNode* screenNode);

	/** 
	 * Set up general entity data
	 * @param name
	 * @param description
	 */
	virtual void setEntityData(const string& name, const string& description);

	/** 
	 * Unset entity data
	 */
	virtual void unsetEntityData();

	/** 
	 * On entity data apply
	 * @param model
	 */
	virtual void onEntityDataApply(LevelEditorEntity* model);

	/** 
	 * Set up entity property preset ids
	 * @param entity property preset ids
	 */
	virtual void setEntityPresetIds(const map<string, vector<PropertyModelClass*>>* entityPresetIds);

	/** 
	 * Set up entity properties
	 * @param entity
	 * @param preset id
	 * @param selected name
	 */
	virtual void setEntityProperties(LevelEditorEntity* entity, const string& presetId, const string& selectedName);

	/** 
	 * Unset entity properties
	 */
	virtual void unsetEntityProperties();

	/** 
	 * On entity property save
	 * @param entity
	 */
	virtual void onEntityPropertySave(LevelEditorEntity* entity);

	/** 
	 * On entity property add
	 * @param entity
	 */
	virtual void onEntityPropertyAdd(LevelEditorEntity* entity);

	/** 
	 * On entity property remove
	 * @param entity
	 */
	virtual void onEntityPropertyRemove(LevelEditorEntity* entity);

	/** 
	 * Shows the error pop up
	 */
	virtual void showErrorPopUp(const string& caption, const string& message);

	/** 
	 * On entity property preset apply
	 * @param model 
	 */
	virtual void onEntityPropertyPresetApply(LevelEditorEntity* model);

	/** 
	 * Event callback for entity properties selection
	 * @pafam entity
	 */
	virtual void onEntityPropertiesSelectionChanged(LevelEditorEntity* entity);

	/** 
	 * On value changed
	 * @param node
	 * @param model
	 */
	virtual void onValueChanged(GUIElementNode* node, LevelEditorEntity* model);

	/** 
	 * On action performed
	 * @param type
	 * @param node
	 * @param entity
	 */
	virtual void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node, LevelEditorEntity* entity);

	/**
	 * Public constructor
	 * @param view
	 * @param on set entity data action
	 */
	EntityBaseSubScreenController(PopUps* popUps, Action* onSetEntityDataAction);

	/**
	 * Destructor
	 */
	virtual ~EntityBaseSubScreenController();
};
