// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileExport.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>

#include <ext/jsonbox/Object.h>
#include <ext/jsonbox/JsonException.h>

using java::io::File;
using java::lang::String;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::_FileSystemException;
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
	static void copyFile(String* source, String* dest) throw (_FileSystemException);

public:

	/** 
	 * Exports a level to a TDME level file
	 * @param file name
	 * @param entity
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void export_(String* pathName, String* fileName, LevelEditorEntity* entity) throw (_FileSystemException, JsonException, ModelFileIOException);

	/** 
	 * Export model meta data file to JSON node
	 * @param entity
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static tdme::ext::jsonbox::Object exportToJSON(LevelEditorEntity* entity) throw (_FileSystemException, JsonException, ModelFileIOException);

};
