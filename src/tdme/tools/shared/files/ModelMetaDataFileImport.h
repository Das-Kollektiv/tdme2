
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <ext/jsonbox/Value.h>
#include <ext/jsonbox/JsonException.h>

using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityLODLevel;
using tdme::os::filesystem::FileSystemException;
using tdme::ext::jsonbox::Value;
using tdme::ext::jsonbox::JsonException;

/** 
 * TDME Model meta data file import
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::ModelMetaDataFileImport final
{
public:
	/** 
	 * Imports a model meta data file from file
	 * @param id id or LevelEditorEntity.ID_NONE
	 * @param pathName path name
	 * @param fileName file name
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 * @return level editor entity
	 */
	static LevelEditorEntity* doImport(int32_t id, const string& pathName, const string& fileName) throw (FileSystemException, JsonException, ModelFileIOException);

	/** 
	 * Imports a model meta data file from JSON object
	 * @param id id or LevelEditorEntity.ID_NONE
	 * @param pathName path name or null
	 * @param jEntityRoot JSON entity root
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 * @return level editor entity
	 */
	static LevelEditorEntity* doImportFromJSON(int32_t id, const string& pathName, Value& jEntityRoot) throw (FileSystemException, JsonException, ModelFileIOException);

	/**
	 * Get resource path name
	 * @param pathName path name within a TDME2 resource folder where parent resource was loaded from
	 * @param fileName file name containing a path and file in a TDME2 resource folder
	 * @return model path name
	 */
	static const string getResourcePathName(const string& pathName, const string& fileName);

private:

	/** 
	 * Parse bounding volume
	 * @param idx idx
	 * @param levelEditorEntity level editor entity
	 * @param pathName path name
	 * @param jBv JSON bounding volume node
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 * @return level editor entity bounding volume
	 */
	static LevelEditorEntityBoundingVolume* parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, const string& pathName, Value& jBv)  throw (FileSystemException, JsonException, ModelFileIOException);

	/**
	 * Parse LOD level
	 * @param pathName path name
	 * @param jLodLevel JSON LOD level
	 * @return level editor lod level
	 */
	static LevelEditorEntityLODLevel* parseLODLevel(const string& pathName, Value& jLodLevel);

	/**
	 * Parse particle system
	 * @param particleSystem particle system to be parsed into
	 * @param pathName path name
	 * @param jParticleSystem JSON particle system object
	 */
	static void parseParticleSystem(LevelEditorEntityParticleSystem* particleSystem, const string& pathName, Value& jParticleSystem);

};
