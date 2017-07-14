// Generated from /tdme/src/tdme/engine/fileio/models/WFObjReader.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Model;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::_FileSystemException;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Wavefront object reader
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::WFObjReader final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Reads a wave front object file
	 * @param path name
	 * @param file name
	 * @return model
	 * @throws _FileSystemException
	 * @throws ModelIOException
	 */
	static Model* read(String* pathName, String* fileName) throw (_FileSystemException, ModelFileIOException);

private:

	/** 
	 * Reads a wavefront object material library
	 * @param path name
	 * @param file name
	 * @throws _FileSystemException
	 * @throws ModelIOException
	 * @return material
	 */
	static _HashMap* readMaterials(String* pathName, String* fileName) throw (_FileSystemException, ModelFileIOException);

	// Generated

public:
	WFObjReader();
protected:
	WFObjReader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
