#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

#include <ext/jsonbox/Object.h>
#include <ext/jsonbox/JsonException.h>

using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::filesystem::FileSystemException;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLODLevel;

using tdme::ext::jsonbox::JsonException;

/** 
 * TDME Model meta data file export
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::ModelMetaDataFileExport final
{
private:

	/** 
	 * Copy file
	 * @param source source
	 * @param dest dest
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void copyFile(const string& source, const string& dest);

	/**
	 * Export LOD level to JSON
	 * @param lodLevel lod level
	 * @return json root
	 */
	static tdme::ext::jsonbox::Object exportLODLevelToJSON(LevelEditorEntityLODLevel* lodLevel);
public:

	/** 
	 * Exports a level to a TDME level file
	 * @param pathName path name
	 * @param fileName file name
	 * @param entity entity
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::ext::jsonbox::JsonException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void export_(const string& pathName, const string& fileName, LevelEditorEntity* entity);

	/** 
	 * Export model meta data file to JSON node
	 * @param entity entity
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::ext::jsonbox::JsonException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static tdme::ext::jsonbox::Object exportToJSON(LevelEditorEntity* entity);

};
