// Generated from /tdme/src/tdme/tools/shared/files/LevelFileExport.java

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
class tdme::tools::shared::files::LevelFileExport final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Exports a level to a TDME level file
	 * @param file name
	 */
	static void export_(String* fileName, LevelEditorLevel* level) /* throws(Exception) */;

	// Generated
	LevelFileExport();
protected:
	LevelFileExport(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
