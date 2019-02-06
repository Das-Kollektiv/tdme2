
#pragma once

#include <map>
#include <string>

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::string;

using tdme::engine::model::Model;
using tdme::engine::model::Material;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::filesystem::FileSystemException;


/** 
 * Wavefront object model reader
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::WFObjReader final
{
public:
	/** 
	 * Reads a wave front object file
	 * @param pathName path name
	 * @param fileName file name
	 * @return model
	 * @throws FileSystemException
	 * @throws ModelIOException
	 */
	static Model* read(const string& pathName, const string& fileName) throw (FileSystemException, ModelFileIOException);

private:

	/** 
	 * Reads a wavefront object material library
	 * @param pathName path name
	 * @param fileName file name
	 * @param materials materials
	 * @throws FileSystemException
	 * @throws ModelIOException
	 */
	static void readMaterials(const string& pathName, const string& fileName, map<string, Material*>* materials) throw (FileSystemException, ModelFileIOException); // TODO: std container: maybe use call by reference
};
