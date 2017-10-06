
#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using std::wstring;

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
	 * @param entity
	 * @param preset id
	 */
	virtual void entityPropertiesPreset(LevelEditorEntity* entity, const wstring& presetId);

	/** 
	 * Save a entity property
	 * @param entity
	 * @param old name
	 * @param name
	 * @param value
	 * @return success
	 */
	virtual bool entityPropertySave(LevelEditorEntity* entity, const wstring& oldName, const wstring& name, const wstring& value);

	/** 
	 * Add a entity property
	 * @param entity
	 * @return success
	 */
	virtual bool entityPropertyAdd(LevelEditorEntity* entity);

	/** 
	 * Remove a entity property from model properties
	 * @param entity
	 * @param name
	 * @return success
	 */
	virtual bool entityPropertyRemove(LevelEditorEntity* entity, const wstring& name);

	/** 
	 * Update current model data
	 * @param entity
	 * @param name
	 * @param description
	 */
	virtual void setEntityData(LevelEditorEntity* entity, const wstring& name, const wstring& description);

	/**
	 * Public constructor
	 * @param model base sub screen controller
	 */
	EntityBaseView(EntityBaseSubScreenController* entityBaseSubScreenController);
};
