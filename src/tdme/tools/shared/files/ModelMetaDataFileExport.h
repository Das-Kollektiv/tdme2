
#pragma once

#include <string>

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
	 * @param source
	 * @param dest
	 * @throws file system exception
	 */
	static void copyFile(const wstring& source, const wstring& dest) throw (FileSystemException);

public:

	/** 
	 * Exports a level to a TDME level file
	 * @param file name
	 * @param entity
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void export_(const wstring& pathName, const wstring& fileName, LevelEditorEntity* entity) throw (FileSystemException, JsonException, ModelFileIOException);

	/** 
	 * Export model meta data file to JSON node
	 * @param entity
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static tdme::ext::jsonbox::Object exportToJSON(LevelEditorEntity* entity) throw (FileSystemException, JsonException, ModelFileIOException);

};
