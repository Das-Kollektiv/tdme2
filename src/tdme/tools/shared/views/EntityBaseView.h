
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using std::string;

using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Model base biew
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityBaseView
{
private:
	EntityBaseSubScreenController* entityBaseSubScreenController {  };

public:

	/** 
	 * Init
	 */
	virtual void initialize();

	/** 
	 * Apply entity property preset
	 * @param entity entity
	 * @param presetId preset id
	 */
	virtual void entityPropertiesPreset(LevelEditorEntity* entity, const string& presetId);

	/** 
	 * Save a entity property
	 * @param entity entity
	 * @param oldName old name
	 * @param name name
	 * @param value value
	 * @return success
	 */
	virtual bool entityPropertySave(LevelEditorEntity* entity, const string& oldName, const string& name, const string& value);

	/** 
	 * Add a entity property
	 * @param entity entity
	 * @return success
	 */
	virtual bool entityPropertyAdd(LevelEditorEntity* entity);

	/** 
	 * Remove a entity property from model properties
	 * @param entity entity
	 * @param name name
	 * @return success
	 */
	virtual bool entityPropertyRemove(LevelEditorEntity* entity, const string& name);

	/** 
	 * Update current model data
	 * @param entity entity
	 * @param name name
	 * @param description description
	 */
	virtual void setEntityData(LevelEditorEntity* entity, const string& name, const string& description);

	/**
	 * Public constructor
	 * @param entityBaseSubScreenController model base sub screen controller
	 */
	EntityBaseView(EntityBaseSubScreenController* entityBaseSubScreenController);
};
