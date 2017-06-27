// Generated from /tdme/src/tdme/tools/shared/views/EntityBaseView.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;


struct default_init_tag;

/** 
 * Model base biew
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityBaseView
	: public virtual Object
{

public:
	typedef Object super;

private:
	EntityBaseSubScreenController* entityBaseSubScreenController {  };
protected:

	/** 
	 * Public constructor
	 * @param model base sub screen controller
	 */
	void ctor(EntityBaseSubScreenController* entityBaseSubScreenController);

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
	virtual void entityPropertiesPreset(LevelEditorEntity* entity, String* presetId);

	/** 
	 * Save a entity property
	 * @param entity
	 * @param old name
	 * @param name
	 * @param value
	 * @return success
	 */
	virtual bool entityPropertySave(LevelEditorEntity* entity, String* oldName, String* name, String* value);

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
	virtual bool entityPropertyRemove(LevelEditorEntity* entity, String* name);

	/** 
	 * Update current model data
	 * @param entity
	 * @param name
	 * @param description
	 */
	virtual void setEntityData(LevelEditorEntity* entity, String* name, String* description);

	// Generated
	EntityBaseView(EntityBaseSubScreenController* entityBaseSubScreenController);
protected:
	EntityBaseView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
