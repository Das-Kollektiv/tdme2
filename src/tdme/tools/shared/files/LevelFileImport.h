// Generated from /tdme/src/tdme/tools/shared/files/LevelFileImport.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::tools::shared::model::LevelEditorLevel;


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
	 */
	static void doImport(String* pathName, String* fileName, LevelEditorLevel* level) /* throws(Exception) */;

	/** 
	 * Imports a level from a TDME level file to Level Editor
	 * @param path name
	 * @param file name
	 * @param level
	 * @param object id prefix
	 */
	static void doImport(String* pathName, String* fileName, LevelEditorLevel* level, String* objectIdPrefix) /* throws(Exception) */;

	// Generated
	LevelFileImport();
protected:
	LevelFileImport(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
