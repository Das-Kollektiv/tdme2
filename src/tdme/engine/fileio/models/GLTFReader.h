#pragma once

#include <string>

#include <ext/tinygltf/tiny_gltf.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystemException;

/**
 * GLTF model reader
 * @author Andreas Drewke
 */
class tdme::engine::fileio::models::GLTFReader final
{
public:

	/**
	 * Reads GLTF file
	 * @param pathName path name
	 * @param fileName file name
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @throws tdme::os::filesystem::FileSystemException
	 * @return model instance
	 */
	static Model* read(const string& pathName, const string& fileName, bool useBC7TextureCompression = true);

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
				return "unknown";
		}
	}

	/**
	 * @return type string
	 */
	inline static string getTypeString(int type) {
		switch (type) {
			case TINYGLTF_TYPE_VEC2:
				return "Vector2";
			case TINYGLTF_TYPE_VEC3:
				return "Vector3";
			case TINYGLTF_TYPE_VEC4:
				return "Vector4";
			case TINYGLTF_TYPE_MAT2:
				return "Matrix2x2";
			case TINYGLTF_TYPE_MAT3:
				return "Matrix3x3";
			case TINYGLTF_TYPE_MAT4:
				return "Matrix4x4";
			case TINYGLTF_TYPE_SCALAR:
				return "Scalar";
			case TINYGLTF_TYPE_VECTOR:
				return "Vector";
			case TINYGLTF_TYPE_MATRIX:
				return "Matrix";
			default:
				return 0;
		}
	}

	/**
	 * Interpolate key frame vectors to our internal 30fps format
	 * @param frameTimeCount frame time count
	 * @param frameTimes frameTimes
	 * @param keyFrameVectors key frame vectors
	 * @param interpolatedVectorCount interpolated vector count
	 * @param interpolatedVectors interpolated vectors
	 * @param frameStartIdx frame start idx
	 */
	static void interpolateKeyFrames(int frameTimeCount, const float* frameTimes, const vector<Vector3>& keyFrameVectors, int interpolatedVectorCount, vector<Vector3>& interpolatedVectors, int frameStartIdx);

	/**
	 * Interpolate key frame quaternions to our internal 30fps format
	 * @param frameTimeCount frame time count
	 * @param frameTimes frameTimes
	 * @param keyFrameQuaternions key frame quaternions
	 * @param interpolatedQuaternionsCount interpolated quaternions count
	 * @param interpolatedQuaternions interpolated quaternions
	 * @param frameStartIdx frame start idx
	 */
	static void interpolateKeyFrames(int frameTimeCount, const float* frameTimes, const vector<Quaternion>& keyFrameQuaternions, int interpolatedQuaternionCount, vector<Quaternion>& interpolatedQuaternions, int frameStartIdx);

	/**
	 * Parse GLTF node
	 * @param pathName model path name
	 * @param fileName model file name
	 * @param gltfModel GLTF mode
	 * @param gltfNodeIdx GLTF node index
	 * @param model TDME model
	 * @param parentNode TDME parent node
	 * @param anonymousNodeIdx anonymous node index
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @return node
	 */
	static Node* parseNode(const string& pathName, const string& fileName, tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Node* parentNode, int& anonymousNodeIdx, bool useBC7TextureCompression);

	/**
	 * Parse GLTF node children into TDME node
	 * @param pathName model path name
	 * @param fileName model file name
	 * @param gltfModel GLTF model
	 * @param gltfNodeChildrenIdx GLTF node children indices
	 * @param parentNode TDME parent node
	 * @param anonymousNodeIdx anonymous node index
	 * @param useBC7TextureCompression use BC7 texture compression
	 */
	static void parseNodeChildren(const string& pathName, const string& fileName, tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Node* parentNode, int& anonymousNodeIdx, bool useBC7TextureCompression);

	/**
	 * Determine texture file name
	 * @param pathName model path name
	 * @param fileName model file name
	 * @param imageName image name
	 * @return file name
	 */
	inline static const string determineTextureFileName(const string& pathName, const string& fileName, const string& imageName) {
		return pathName + "/" + fileName + "-" + imageName + ".png";
	}

	/**
	 * Compute tangents and bitangents
	 * @param node node
	 */
	static void computeTangentsAndBitangents(Node* node);

	/**
	 * Get node scale vector
	 * @param gltfModel GLTF model
	 * @param nodeId node id
	 * @return scale vector of given node
	 */
	static const Vector3 getNodeScaleVector(const tinygltf::Model& gltfModel, const string& nodeId);

	/**
	 * Get node rotation quaternion
	 * @param gltfModel GLTF model
	 * @param nodeId node id
	 * @return rotation quaternion of given node
	 */
	static const Quaternion getNodeRotationQuaternion(const tinygltf::Model& gltfModel, const string& nodeId);

	/**
	 * Get node translation vector
	 * @param gltfModel GLTF model
	 * @param nodeId node id
	 * @return translation vector of given node
	 */
	static const Vector3 getNodeTranslationVector(const tinygltf::Model& gltfModel, const string& nodeId);

};
