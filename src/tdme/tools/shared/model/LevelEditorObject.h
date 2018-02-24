
#pragma once

#include <string>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/model/ModelProperties.h>

using std::string;

using tdme::tools::shared::model::ModelProperties;
using tdme::engine::Transformations;
using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Level Editor Object
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorObject final
	: public ModelProperties
{
private:
	string id {  };
	string description {  };
	Transformations transformations {  };
	LevelEditorEntity* entity {  };

public:

	/** 
	 * @return id
	 */
	const string& getId();

	/** 
	 * Set id
	 * @param id
	 */
	void setId(const string& id);

	/** 
	 * @return description
	 */
	const string& getDescription();

	/** 
	 * Set description
	 * @param description
	 */
	void setDescription(const string& description);

	/** 
	 * @return transformations
	 */
	Transformations& getTransformations();

	/** 
	 * @return entity
	 */
	LevelEditorEntity* getEntity();

	/** 
	 * Set up entity
	 * @param entity
	 */
	void setEntity(LevelEditorEntity* entity);

	/** 
	 * @return merged properties from entity and object
	 */
	ModelProperties* getTotalProperties();

public:
	/**
	 * Public constructor
	 * @param id
	 * @param transformations
	 * @param entity
	 */
	LevelEditorObject(const string& id, const string& description, const Transformations& transformations, LevelEditorEntity* entity);

	/**
	 * Destructor
	 */
	virtual ~LevelEditorObject();

};
