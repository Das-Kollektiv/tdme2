// Generated from /tdme/src/tdme/tools/shared/files/LevelFileExport.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

#include <java/lang/Object.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <ext/jsonbox/JsonException.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::_FileSystemException;
using tdme::tools::shared::model::LevelEditorLevel;

using tdme::ext::jsonbox::JsonException;

struct default_init_tag;

/** 
 * TDME Level Editor File Export
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::LevelFileExport final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Exports a level to a TDME level file
	 * @param path name
	 * @param file name
	 * @param level
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void export_(String* pathName, String* fileName, LevelEditorLevel* level) throw (_FileSystemException, JsonException, ModelFileIOException);

	// Generated
	LevelFileExport();
protected:
	LevelFileExport(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
