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
	static size_t getComponentTypeByteSize(int type);

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
	 * @param parentGroup TDME parent group
	 */
	static Group* parseNode(const string& pathName, const tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Group* parentGroup);

	/**
	 * Parse GLTF node children into TDME group
	 * @param pathName path name
	 * @param gltfModel GLTF model
	 * @param gltfNodeChildrenIdx GLTF node children indices
	 * @param parentGroup TDME parent group
	 */
	static void parseNodeChildren(const string& pathName, const tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Group* parentGroup);

	/**
	 * Write PNG from memory
	 * @param pathName path name
	 * @param fileName file name
	 * @param bitsPerPixel bits per pixel (24 or 32)
	 * @param width width
	 * @param height height
	 * @param pixels pixels
	 */
	static bool writePNG(const string& pathName, const string& fileName, int bitsPerPixel, int width, int height, const uint8_t* pixels);

	/**
	 * Determine texture file name
	 * @param fileName
	 * @return file name
	 */
	static string determineTextureFileName(const string& imageName);
};
