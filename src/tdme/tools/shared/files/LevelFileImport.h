// Generated from /tdme/src/tdme/tools/shared/files/LevelFileImport.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>
#include <ext/jsonbox/JsonException.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::os::_FileSystemException;

using tdme::ext::jsonbox::JsonException;


struct default_init_tag;

/** 
 * TDME Level Editor File Export
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::LevelFileImport final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Imports a level from a TDME level file to Level Editor
	 * @param game root
	 * @param path name
	 * @param file name
	 * @param level
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void doImport(String* pathName, String* fileName, LevelEditorLevel* level) throw (_FileSystemException, JsonException, ModelFileIOException);

	/** 
	 * Imports a level from a TDME level file to Level Editor
	 * @param path name
	 * @param file name
	 * @param level
	 * @param object id prefix
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void doImport(String* pathName, String* fileName, LevelEditorLevel* level, String* objectIdPrefix) throw (_FileSystemException, JsonException, ModelFileIOException);

	// Generated
	LevelFileImport();
protected:
	LevelFileImport(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
