#pragma once

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
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
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::Skinning;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystemException;

namespace tdme {
namespace engine {
namespace fileio {
namespace models {

/**
 * TM writer output stream
 * @author Andreas Drewke
 */
class TMWriterOutputStream {
private:
	vector<uint8_t>* data;
public:

	/**
	 * Constructor
	 * @param data data vector to write TM to
	 */
	inline TMWriterOutputStream(vector<uint8_t>* data) {
		this->data = data;
	}

	/**
	 * Get data
	 * @return data
	 */
	inline vector<uint8_t>* getData() {
		return data;
	}

	/**
	 * Writes a boolean to output stream
	 * @throws model file IO exception
	 * @param b boolean
	 */
	inline void writeBoolean(bool b) {
		writeByte(b == true?1:0);
	}

	/**
	 * Writes a byte to output stream
	 * @throws model file IO exception
	 * @param b byte
	 */
	inline void writeByte(uint8_t b) {
		data->push_back(b);
	}

	/**
	 * Writes a integer to output stream
	 * @throws model file IO exception
	 * @param i int
	 */
	inline void writeInt(int32_t i) {
		writeByte((i >> 24) & 0xFF);
		writeByte((i >> 16) & 0xFF);
		writeByte((i >> 8) & 0xFF);
		writeByte((i >> 0) & 0xFF);
	}

	/**
	 * Writes a float to output stream
	 * @param f float
	 * @throws model file IO exception
	 */
	inline void writeFloat(float f) {
		int value = *((int*)&f);
		writeInt(value);
	}

	/**
	 * Writes a string to output stream
	 * @param s string
	 * @throws model file IO exception
	 */
	inline void writeString(const string& s) {
		if (s.size() == 0) {
			writeBoolean(false);
		} else {
			writeBoolean(true);
			writeInt(s.size());
			for (auto i = 0; i < s.size(); i++) {
				writeByte(static_cast<uint8_t>(s[i]));
			}
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param f float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(const array<float,2>& f) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param f float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(const array<float,3>& f) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param f float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(const array<float,4>& f) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param f float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(const array<float,9>& f) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param f float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(const array<float,16>& f) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param f float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(const vector<float>& f) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a uint8_t array to output stream, note that no size information is given in this case
	 * @param d uint8_t array
	 * @throws model file IO exception
	 */
	inline void writeUInt8tArray(const vector<uint8_t>& d) {
		for (auto i = 0; i < d.size(); i++) {
			writeByte(d[i]);
		}
	}

};

};
};
};
};

/**
 * TDME model writer
 * @author Andreas Drewke
 */
class tdme::engine::fileio::models::TMWriter
{
public:

	/**
	 * TDME model format writer
	 * @param model model
	 * @param pathName path name
	 * @param fileName file name
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void write(Model* model, const string& pathName, const string& fileName, bool useBC7TextureCompression = true);

	/**
	 * TDME model format writer
	 * @param model model
	 * @param data data to write TM to
	 * @param useBC7TextureCompression use BC7 texture compression
	 */
	static void write(Model* model, vector<uint8_t>& data, bool useBC7TextureCompression = true);

private:

	/**
	 * Write embedded textures
	 * @param os output stream
	 * @param m model
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws model file IO exception
	 */
	static void writeEmbeddedTextures(TMWriterOutputStream* os, Model* m, bool useBC7TextureCompression);

	/**
	 * Write material
	 * @param os output stream
	 * @param m material
	 * @throws model file IO exception
	 */
	static void writeMaterial(TMWriterOutputStream* os, Material* m);

	/**
	 * Write animation setup
	 * @param os output stream
	 * @param animationSetup animation setup
	 * @throws model file IO exception
	 */
	static void writeAnimationSetup(TMWriterOutputStream* os, AnimationSetup* animationSetup);

	/**
	 * Write vertices to output stream
	 * @param os output stream
	 * @param v vertices
	 * @throws model file IO exception
	 */
	static void writeVertices(TMWriterOutputStream* os, const vector<Vector3>& v);

	/**
	 * Write texture coordinates to output stream
	 * @param os output stream
	 * @param tc texture coordinates
	 * @throws model file IO exception
	 */
	static void writeTextureCoordinates(TMWriterOutputStream* os, const vector<Vector2>& tc);

	/**
	 * Write indices to output stream
	 * @param os output stream
	 * @param indices indices
	 * @throws model file IO exception
	 */
	static void writeIndices(TMWriterOutputStream* os, const array<int32_t, 3>& indices);

	/**
	 * Write animation to output stream
	 * @param os output stream
	 * @param a animation
	 * @throws model file IO exception
	 */
	static void writeAnimation(TMWriterOutputStream* os, Animation* a);

	/**
	 * Write faces entities to output stream
	 * @param os output stream
	 * @param facesEntities faces entities
	 * @throws model file IO exception
	 */
	static void writeFacesEntities(TMWriterOutputStream* os, const vector<FacesEntity>& facesEntities);

	/**
	 * Write skinning joint
	 * @param os output stream
	 * @param joint joint
	 * @throws model file IO exception
	 */
	static void writeSkinningJoint(TMWriterOutputStream* os, const Joint& joint);

	/**
	 * Write skinning joint weight
	 * @param os output stream
	 * @param jointWeight joint
	 * @throws model file IO exception
	 */
	static void writeSkinningJointWeight(TMWriterOutputStream* os, const JointWeight& jointWeight);

	/**
	 * Write skinning to output stream
	 * @param os output stream
	 * @param skinning skinning
	 * @throws model file IO exception
	 */
	static void writeSkinning(TMWriterOutputStream* os, Skinning* skinning);

	/**
	 * Write sub nodes
	 * @param os output stream
	 * @param subNodes sub nodes
	 * @throws model file IO exception
	 */
	static void writeSubNodes(TMWriterOutputStream* os, const unordered_map<string, Node*>& subNodes);

	/**
	 * Write node to output stream
	 * @param os output stream
	 * @param g node
	 * @throws model file IO exception
	 */
	static void writeNode(TMWriterOutputStream* os, Node* g);

	/**
	 * Write thumbnail to output stream
	 * @param os output stream
	 * @param model model
	 * @throws model file IO exception
	 */
	static void writeThumbnail(TMWriterOutputStream* os, Model* model);

};
