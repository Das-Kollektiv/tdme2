
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using std::string;

using tdme::tools::shared::controller::PrototypeBaseSubScreenController;
using tdme::engine::prototype::Prototype;

/**
 * Model base biew
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityBaseView final
{
private:
	PrototypeBaseSubScreenController* prototypeBaseSubScreenController { nullptr };

public:
	/**
	 * Public constructor
	 * @param prototypeBaseSubScreenController model base sub screen controller
	 */
	EntityBaseView(PrototypeBaseSubScreenController* prototypeBaseSubScreenController);

	/**
	 * Init
	 */
	void initialize();

	/**
	 * Apply entity property preset
	 * @param entity entity
	 * @param presetId preset id
	 */
	void entityPropertiesPreset(Prototype* entity, const string& presetId);

	/**
	 * Save a entity property
	 * @param entity entity
	 * @param oldName old name
	 * @param name name
	 * @param value value
	 * @return success
	 */
	bool entityPropertySave(Prototype* entity, const string& oldName, const string& name, const string& value);

	/**
	 * Add a entity property
	 * @param entity entity
	 * @return success
	 */
	bool entityPropertyAdd(Prototype* entity);

	/**
	 * Remove a entity property from model properties
	 * @param entity entity
	 * @param name name
	 * @return success
	 */
	bool entityPropertyRemove(Prototype* entity, const string& name);

	/**
	 * Update current model data
	 * @param entity entity
	 * @param name name
	 * @param description description
	 */
	void setEntityData(Prototype* entity, const string& name, const string& description);

};
