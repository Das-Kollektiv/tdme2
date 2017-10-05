// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileImport.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <ext/jsonbox/Value.h>
#include <ext/jsonbox/JsonException.h>

using std::wstring;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::os::filesystem::_FileSystemException;
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
	static LevelEditorEntity* doImport(int32_t id, const wstring& pathName, const wstring& fileName) throw (_FileSystemException, JsonException, ModelFileIOException);

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
	static LevelEditorEntity* doImportFromJSON(int32_t id, const wstring& pathName, Value& jEntityRoot) throw (_FileSystemException, JsonException, ModelFileIOException);

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
	static LevelEditorEntityBoundingVolume* parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, const wstring& pathName, Value& jBv)  throw (_FileSystemException, JsonException, ModelFileIOException);
};
