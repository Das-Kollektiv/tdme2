
#pragma once

#include <string>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/model/ModelProperties.h>

using std::wstring;

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
	wstring id {  };
	wstring description {  };
	Transformations* transformations {  };
	LevelEditorEntity* entity {  };

public:

	/** 
	 * @return id
	 */
	const wstring& getId();

	/** 
	 * Set id
	 * @param id
	 */
	void setId(const wstring& id);

	/** 
	 * @return description
	 */
	const wstring& getDescription();

	/** 
	 * Set description
	 * @param description
	 */
	void setDescription(const wstring& description);

	/** 
	 * @return transformations
	 */
	Transformations* getTransformations();

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
	LevelEditorObject(const wstring& id, const wstring& description, Transformations* transformations, LevelEditorEntity* entity);

};
