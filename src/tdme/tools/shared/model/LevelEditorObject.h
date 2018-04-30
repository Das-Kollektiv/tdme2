
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
	inline const string& getId() {
		return id;
	}

	/** 
	 * Set id
	 * @param id
	 */
	inline void setId(const string& id) {
		this->id = id;
	}

	/** 
	 * @return description
	 */
	inline const string& getDescription() {
		return description;
	}

	/** 
	 * Set description
	 * @param description
	 */
	inline void setDescription(const string& description) {
		this->description = description;
	}

	/** 
	 * @return transformations
	 */
	inline Transformations& getTransformations() {
		return transformations;
	}

	/** 
	 * @return entity
	 */
	inline LevelEditorEntity* getEntity() {
		return entity;
	}

	/** 
	 * Set up entity
	 * @param entity
	 */
	inline void setEntity(LevelEditorEntity* entity) {
		this->entity = entity;
	}

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
