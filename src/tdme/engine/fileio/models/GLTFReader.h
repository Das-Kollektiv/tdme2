#pragma once

#include <string>

#include <ext/tinygltf/tiny_gltf.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/os/filesystem/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Model;
using tdme::engine::model::Group;
using tdme::os::filesystem::FileSystemException;

/** 
 * Collada DAE model reader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::GLTFReader final
{
public:

	/** 
	 * Reads GLTF file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @throws tdme::os::filesystem::FileSystemException
	 * @return model instance
	 */
	static Model* read(const string& pathName, const string& fileName);

private:

	/**
	 * @return component byte size
	 */
	static size_t getComponentTypeByteSize(int type);

	/**
	 * Parse GLTF node
	 * @param gltfModel GLTF mode
	 * @param gltfNodeIdx GLTF node index
	 * @param model TDME model 
	 * @param parentGroup TDME parent group
	 */
	static Group* parseNode(const tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Group* parentGroup);

	/**
	 * Parse GLTF node children into TDME group
	 * @param gltfModel GLTF model
	 * @param gltfNodeChildrenIdx GLTF node children indices
	 * @param parentGroup TDME parent group
	 */
	static void parseNodeChildren(const tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Group* parentGroup); 
};
