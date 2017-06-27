// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileExport.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/json/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::File;
using java::lang::String;
using org::json::JSONObject;
using tdme::tools::shared::model::LevelEditorEntity;


struct default_init_tag;

/** 
 * TDME Model meta data file export
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::ModelMetaDataFileExport final
	: public Object
{

public:
	typedef Object super;

private:

	/** 
	 * Copy file
	 * @param source
	 * @param dest
	 * @throws IOException
	 */
	static void copyFile(File* source, File* dest) /* throws(IOException) */;

public:

	/** 
	 * Exports a level to a TDME level file
	 * @param file name
	 * @param entity
	 */
	static void export_(String* pathName, String* fileName, LevelEditorEntity* entity) /* throws(Exception) */;

	/** 
	 * Export model meta data file to JSON node
	 * @param entity
	 */
	static JSONObject* exportToJSON(LevelEditorEntity* entity) /* throws(Exception) */;

	// Generated
	ModelMetaDataFileExport();
protected:
	ModelMetaDataFileExport(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
