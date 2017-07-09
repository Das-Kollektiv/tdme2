// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileImport.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/json/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <ext/jsonbox/Value.h>
#include <java/lang/Object.h>


using java::lang::Object;
using java::lang::String;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::ext::jsonbox::Value;


struct default_init_tag;

/** 
 * TDME Model meta data file import
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::ModelMetaDataFileImport final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Imports a model meta data file from file
	 * @param id or LevelEditorEntity.ID_NONE
	 * @param path name
	 * @param file name
	 */
	static LevelEditorEntity* doImport(int32_t id, String* pathName, String* fileName) /* throws(Exception) */;

	/** 
	 * Imports a model meta data file from JSON object
	 * @param id or LevelEditorEntity.ID_NONE
	 * @param path name or null
	 * @param JSON entity root
	 */
	static LevelEditorEntity* doImportFromJSON(int32_t id, String* pathName, Value& jEntityRoot) /* throws(Exception) */;

private:

	/** 
	 * Parse bounding volume
	 * @param idx
	 * @param level editor entity
	 * @param JSON bounding volume node
	 * @return level editor entity bounding volume
	 * @throws JSONException
	 */
	static LevelEditorEntityBoundingVolume* parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, Value& jBv) /* throws(JSONException) */;

	// Generated

public:
	ModelMetaDataFileImport();
protected:
	ModelMetaDataFileImport(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
