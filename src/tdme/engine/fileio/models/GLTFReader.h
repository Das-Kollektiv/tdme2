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
using tdme::engine::model::Node;
using tdme::os::filesystem::FileSystemException;

/**
 * GLTF model reader
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
	inline static size_t getComponentTypeByteSize(int type) {
		switch (type) {
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
			case TINYGLTF_COMPONENT_TYPE_BYTE:
				return sizeof(char);
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
			case TINYGLTF_COMPONENT_TYPE_SHORT:
				return sizeof(short);
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
			case TINYGLTF_COMPONENT_TYPE_INT:
				return sizeof(int);
			case TINYGLTF_COMPONENT_TYPE_FLOAT:
				return sizeof(float);
			case TINYGLTF_COMPONENT_TYPE_DOUBLE:
				return sizeof(double);
			default:
				return 0;
		}
	}

	/**
	 * @return component type string
	 */
	inline static string getComponentTypeString(int type) {
		switch (type) {
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
				return "uint8_t";
			case TINYGLTF_COMPONENT_TYPE_BYTE:
				return "int8_t";
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
				return "uint16_t";
			case TINYGLTF_COMPONENT_TYPE_SHORT:
				return "int16_t";
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
				return "uint32_t";
			case TINYGLTF_COMPONENT_TYPE_INT:
				return "int32_t";
			case TINYGLTF_COMPONENT_TYPE_FLOAT:
				return "float";
			case TINYGLTF_COMPONENT_TYPE_DOUBLE:
				return "double";
			default:
				return 0;
		}
	}

	/**
	 * Interpolate key frames to our internal 30fps format
	 * @param frameTimeCount frame time count
	 * @param frameTimes frameTimes
	 * @param keyFrameMatrices key frame matrices
	 * @param interpolatedMatrixCount interpolated matrix count
	 * @param interpolatedMatrices interpolated matrices
	 * @param frameStartIdx frame start idx
	 */
	static void interpolateKeyFrames(int frameTimeCount, const float* frameTimes, const vector<Matrix4x4>& keyFrameMatrices, int interpolatedMatrixCount, vector<Matrix4x4>& interpolatedMatrices, int frameStartIdx);

	/**
	 * Parse GLTF node
	 * @param pathName path name
	 * @param gltfModel GLTF mode
	 * @param gltfNodeIdx GLTF node index
	 * @param model TDME model
	 * @param parentNode TDME parent node
	 */
	static Node* parseNode(const string& pathName, const tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Node* parentNode);

	/**
	 * Parse GLTF node children into TDME node
	 * @param pathName path name
	 * @param gltfModel GLTF model
	 * @param gltfNodeChildrenIdx GLTF node children indices
	 * @param parentNode TDME parent node
	 */
	static void parseNodeChildren(const string& pathName, const tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Node* parentNode);

	/**
	 * Determine texture file name
	 * @param fileName
	 * @return file name
	 */
	static string determineTextureFileName(const string& imageName);
};
