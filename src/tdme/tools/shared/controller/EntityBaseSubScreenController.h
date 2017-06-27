// Generated from /tdme/src/tdme/tools/shared/controller/EntityBaseSubScreenController.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Iterable;
using java::lang::String;
using java::util::Collection;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::EntityBaseView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * Entity base sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::EntityBaseSubScreenController
	: public virtual Object
{

public:
	typedef Object super;

private:
	static MutableString* TEXT_EMPTY;
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
protected:

	/** 
	 * Public constructor
	 * @param view
	 * @param on set entity data action
	 */
	void ctor(PopUps* popUps, Action* onSetEntityDataAction);

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
	virtual void setEntityData(String* name, String* description);

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
	virtual void setEntityPresetIds(Collection* entityPresetIds);

	/** 
	 * Set up entity properties
	 * @param model
	 * @param preset id
	 * @param entity properties
	 * @param selected name
	 */
	virtual void setEntityProperties(LevelEditorEntity* model, String* presetId, Iterable* entityProperties, String* selectedName);

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
	virtual void showErrorPopUp(String* caption, String* message);

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

	// Generated
	EntityBaseSubScreenController(PopUps* popUps, Action* onSetEntityDataAction);
protected:
	EntityBaseSubScreenController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
