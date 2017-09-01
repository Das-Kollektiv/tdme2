// Generated from /tdme/src/tdme/engine/fileio/models/WFObjReader.java

#pragma once

#include <map>
#include <string>

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>

using std::map;
using std::wstring;

using tdme::engine::model::Model;
using tdme::engine::model::Material;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::_FileSystemException;


/** 
 * Wavefront object reader
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::WFObjReader final
{
public:
	/** 
	 * Reads a wave front object file
	 * @param path name
	 * @param file name
	 * @return model
	 * @throws _FileSystemException
	 * @throws ModelIOException
	 */
	static Model* read(const wstring& pathName, const wstring& fileName) throw (_FileSystemException, ModelFileIOException);

private:

	/** 
	 * Reads a wavefront object material library
	 * @param path name
	 * @param file name
	 * @param materials
	 * @throws _FileSystemException
	 * @throws ModelIOException
	 */
	static void readMaterials(const wstring& pathName, const wstring& fileName, map<wstring, Material*>* materials) throw (_FileSystemException, ModelFileIOException);
};
