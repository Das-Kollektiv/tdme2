// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorObject.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/model/ModelProperties.h>

using tdme::tools::shared::model::ModelProperties;
using java::lang::String;
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
	String* id {  };
	String* description {  };
	Transformations* transformations {  };
	LevelEditorEntity* entity {  };

public:

	/** 
	 * @return id
	 */
	String* getId();

	/** 
	 * Set id
	 * @param id
	 */
	void setId(String* id);

	/** 
	 * @return description
	 */
	String* getDescription();

	/** 
	 * Set description
	 * @param description
	 */
	void setDescription(String* description);

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
	LevelEditorObject(String* id, String* description, Transformations* transformations, LevelEditorEntity* entity);

};
