#pragma once

#include <tdme/tdme.h>

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::array;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::Texture;
using tdme::engine::model::Animation;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystemException;

namespace tdme {
namespace engine {
namespace fileio {
namespace models {

/**
 * TM reader input stream
 * @author Andreas Drewke
 */
class TMReaderInputStream {
private:
	const vector<uint8_t>* data;
	int position;
public:
	/**
	 * Constructor
	 * @param data input data array
	 */
	inline TMReaderInputStream(const vector<uint8_t>* data): data(data), position(0) {
	}

	/**
	 * Reads a boolean from input stream
	 * @throws model file IO exception
	 * @return boolean
	 */
	inline bool readBoolean() {
		return readByte() == 1;
	}

	/**
	 * Reads a byte from input stream
	 * @throws model file IO exception
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return byte
	 */
	inline int8_t readByte() {
		if (position == data->size()) {
			throw ModelFileIOException("Unexpected end of stream");
		}
		return (*data)[position++];
	}

	/**
	 * Reads a integer from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return int
	 */
	inline  int32_t readInt() {
		int32_t value =
			((static_cast<int32_t>(readByte()) & 0xFF) << 24) +
			((static_cast<int32_t>(readByte()) & 0xFF) << 16) +
			((static_cast<int32_t>(readByte()) & 0xFF) << 8) +
			((static_cast<int32_t>(readByte()) & 0xFF) << 0);
		return value;
	}

	/**
	 * Reads a float from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return float
	 */
	inline float readFloat() {
		int32_t value =
			((static_cast<int32_t>(readByte()) & 0xFF) << 24) +
			((static_cast<int32_t>(readByte()) & 0xFF) << 16) +
			((static_cast<int32_t>(readByte()) & 0xFF) << 8) +
			((static_cast<int32_t>(readByte()) & 0xFF) << 0);
		float* floatValue = (float*)&value;
		return *floatValue;
	}

	/**
	 * Reads a string from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return string
	 */
	inline const string readString() {
		if (readBoolean() == false) {
			return "";
		} else {
			auto l = readInt();
			string s;
			for (auto i = 0; i < l; i++) {
				s+= static_cast<char>(readByte());
			}
			return s;
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return float array
	 */
	inline void readFloatArray(array<float, 16>& data) {
		auto length = readInt();
		if (length != data.size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data.size(); i++) {
			(data)[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return float array
	 */
	inline void readFloatArray(array<float, 9>& data) {
		auto length = readInt();
		if (length != data.size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data.size(); i++) {
			(data)[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return float array
	 */
	inline void readFloatArray(array<float, 4>& data) {
		auto length = readInt();
		if (length != data.size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data.size(); i++) {
			(data)[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return float array
	 */
	inline void readFloatArray(array<float, 3>& data) {
		auto length = readInt();
		if (length != data.size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data.size(); i++) {
			data[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return float array
	 */
	inline void readFloatArray(array<float, 2>& data) {
		auto length = readInt();
		if (length != data.size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data.size(); i++) {
			data[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return float array
	 */
	inline const vector<float> readFloatVector() {
		vector<float> f;
		f.resize(readInt());
		for (auto i = 0; i < f.size(); i++) {
			f[i] = readFloat();
		}
		return f;
	}

};

};
};
};
};

/**
 * TDME model reader
 * @author Andreas Drewke
 */
class tdme::engine::fileio::models::TMReader
{
public:

	/**
	 * TDME model format reader
	 * @param pathName path name
	 * @param fileName file name
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return model
	 */
	static Model* read(const string& pathName, const string& fileName, bool useBC7TextureCompression = true);

	/**
	 * TDME model format reader
	 * @param data data vector to read TM from
	 * @param pathName path name file was read from
	 * @param fileName file name was read from
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return model
	 */
	static Model* read(const vector<uint8_t>& data, const string& pathName = string(), const string& fileName = string(), bool useBC7TextureCompression = true);

private:
	/**
	 * Get texture path
	 * @param modelPathName model path name
	 * @param texturePathName texture path name
	 * @param textureFileName texture file name
	 */
	static const string getTexturePath(const string& modelPathName, const string& texturePathName, const string& textureFileName);

	/**
	 * Read material
	 * @param embeddedTextures embedded textures
	 * @param fileName file name
	 * @return material or nullptr
	 */
	inline static Texture* getEmbeddedTexture(const unordered_map<string, Texture*>& embeddedTextures, const string& fileName) {
		auto embeddedTextureIt = embeddedTextures.find(fileName);
		if (embeddedTextureIt == embeddedTextures.end()) return nullptr;
		auto embeddedTexture = embeddedTextureIt->second;
		embeddedTexture->acquireReference();
		return embeddedTexture;
	}

	/**
	 * Read material
	 * @param pathName path name
	 * @param is input stream
	 * @param embeddedTextures embedded textures
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @param version version
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return material
	 */
	static void readEmbeddedTextures(TMReaderInputStream* is, unordered_map<string, Texture*>& embeddedTextures, const array<uint8_t, 3>& version);

	/**
	 * Read material
	 * @param pathName path name
	 * @param is input stream
	 * @param model model
	 * @param embeddedTextures embedded textures
	 * @param version version
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return material
	 */
	static Material* readMaterial(const string& pathName, TMReaderInputStream* is, Model* model, const unordered_map<string, Texture*>& embeddedTextures, bool useBC7TextureCompression, const array<uint8_t, 3>& version);

	/**
	 * Read animation setup
	 * @param is input stream
	 * @param model model
	 * @param version version
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void readAnimationSetup(TMReaderInputStream* is, Model* model, const array<uint8_t, 3>& version);

	/**
	 * Read vertices from input stream
	 * @param is input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return vector3 array
	 */
	static const vector<Vector3> readVertices(TMReaderInputStream* is);

	/**
	 * Read texture coordinates from input stream
	 * @param is input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return texture coordinates array
	 */
	static const vector<Vector2> readTextureCoordinates(TMReaderInputStream* is);

	/**
	 * Read indices from input stream
	 * @param is input stream
	 * @param indices indices
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return if having indices
	 */
	static bool readIndices(TMReaderInputStream* is, array<int32_t, 3>* indices);

	/**
	 * Read animation from input stream into node
	 * @param is input stream
	 * @param g node
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return Animation
	 */
	static Animation* readAnimation(TMReaderInputStream* is, Node* g);

	/**
	 * Read faces entities from input stream
	 * @param is input stream
	 * @param g node
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void readFacesEntities(TMReaderInputStream* is, Node* g);

	/**
	 * Read skinning joint
	 * @param is input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return joint
	 */
	static Joint readSkinningJoint(TMReaderInputStream* is);

	/**
	 * Read skinning joint weight
	 * @param is input stream
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return joint weight
	 */
	static JointWeight readSkinningJointWeight(TMReaderInputStream* is);

	/**
	 * Read skinning from input stream
	 * @param is input stream
	 * @param g node
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void readSkinning(TMReaderInputStream* is, Node* g);

	/**
	 * Read sub nodes
	 * @param is input stream
	 * @param model model
	 * @param parentNode parent node
	 * @param subNodes sub nodes
	 * @throws IOException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return node
	 */
	static void readSubNodes(TMReaderInputStream* is, Model* model, Node* parentNode, unordered_map<string, Node*>& subNodes);

	/**
	 * Write node to output stream
	 * @param is input stream
	 * @param model model
	 * @param parentNode parent node
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return node
	 */
	static Node* readNode(TMReaderInputStream* is, Model* model, Node* parentNode);
};
