#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <ext/jsonbox/JsonException.h>

using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::filesystem::FileSystemException;
using tdme::tools::shared::model::LevelEditorLevel;

using tdme::ext::jsonbox::JsonException;

/** 
 * TDME Level Editor File Export
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::LevelFileExport final
{

public:
	/** 
	 * Exports a level to a TDME level file
	 * @param pathName path name
	 * @param fileName file name
	 * @param level level
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void export_(const string& pathName, const string& fileName, LevelEditorLevel* level) throw (FileSystemException, JsonException, ModelFileIOException);

};
