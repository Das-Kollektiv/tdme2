// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileImport.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

#include <java/lang/Object.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>
#include <ext/jsonbox/Value.h>
#include <ext/jsonbox/JsonException.h>


using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::os::_FileSystemException;
using tdme::ext::jsonbox::Value;
using tdme::ext::jsonbox::JsonException;


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
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 * @return level editor entity
	 */
	static LevelEditorEntity* doImport(int32_t id, String* pathName, String* fileName) throw (_FileSystemException, JsonException, ModelFileIOException);

	/** 
	 * Imports a model meta data file from JSON object
	 * @param id or LevelEditorEntity.ID_NONE
	 * @param path name or null
	 * @param JSON entity root
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 * @return level editor entity
	 */
	static LevelEditorEntity* doImportFromJSON(int32_t id, String* pathName, Value& jEntityRoot) throw (_FileSystemException, JsonException, ModelFileIOException);

private:

	/** 
	 * Parse bounding volume
	 * @param idx
	 * @param level editor entity
	 * @param path name
	 * @param JSON bounding volume node
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 * @return level editor entity bounding volume
	 */
	static LevelEditorEntityBoundingVolume* parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, String* pathName, Value& jBv)  throw (_FileSystemException, JsonException, ModelFileIOException);

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
