
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
	 * @param id or LevelEditorEntity.ID_NONE
	 * @param path name
	 * @param file name
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 * @return level editor entity
	 */
	static LevelEditorEntity* doImport(int32_t id, const string& pathName, const string& fileName) throw (FileSystemException, JsonException, ModelFileIOException);

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
	static LevelEditorEntity* doImportFromJSON(int32_t id, const string& pathName, Value& jEntityRoot) throw (FileSystemException, JsonException, ModelFileIOException);

private:

	/**
	 * Get model path name
	 * @param path name
	 * @param file name
	 * @return model path name
	 */
	static const string getModelPathName(const string& pathName, const string& fileName);

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
	static LevelEditorEntityBoundingVolume* parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, const string& pathName, Value& jBv)  throw (FileSystemException, JsonException, ModelFileIOException);
};
