#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::array;
using std::map;
using std::vector;
using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystemException;

namespace tdme {
namespace engine {
namespace fileio {
namespace models {

/**
 * TM writer output stream
 * @author Andreas Drewke
 * @version $Id$
 */
class TMWriterOutputStream {
private:
	vector<uint8_t> data;
public:

	/**
	 * Constructor
	 */
	inline TMWriterOutputStream() throw (ModelFileIOException) {
	}

	/**
	 * Get data
	 * @return data
	 */
	inline vector<uint8_t>* getData() {
		return &data;
	}

	/**
	 * Writes a boolean to output stream
	 * @throws model file IO exception
	 * @param boolean
	 */
	inline void writeBoolean(bool b) throw (ModelFileIOException) {
		writeByte(b == true?1:0);
	}

	/**
	 * Writes a byte to output stream
	 * @throws model file IO exception
	 * @param byte
	 */
	inline void writeByte(int8_t b) throw (ModelFileIOException) {
		data.push_back(b);
	}

	/**
	 * Writes a integer to output stream
	 * @throws model file IO exception
	 * @param int
	 */
	inline void writeInt(int32_t i) throw (ModelFileIOException) {
		writeByte((i >> 24) & 0xFF);
		writeByte((i >> 16) & 0xFF);
		writeByte((i >> 8) & 0xFF);
		writeByte((i >> 0) & 0xFF);
	}

	/**
	 * Writes a float to output stream
	 * @param float
	 * @throws model file IO exception
	 */
	inline void writeFloat(float f) throw (ModelFileIOException) {
		int value = *((int*)&f);
		writeInt(value);
	}

	/**
	 * Writes a string to output stream
	 * @param string
	 * @throws model file IO exception
	 */
	inline void writeString(const string& s) throw (ModelFileIOException) {
		if (s.size() == 0) {
			writeBoolean(false);
		} else {
			writeBoolean(true);
			writeInt(s.size());
			for (auto i = 0; i < s.size(); i++) {
				writeByte(static_cast< uint8_t >(s[i]));
			}
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(array<float,2>& f) throw (ModelFileIOException) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(array<float,3>& f) throw (ModelFileIOException) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(array<float,4>& f) throw (ModelFileIOException) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(array<float,4>* f) throw (ModelFileIOException) {
		writeInt(f->size());
		for (auto i = 0; i < f->size(); i++) {
			writeFloat((*f)[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(array<float,16>& f) throw (ModelFileIOException) {
		writeInt(f.size());
		for (auto i = 0; i < f.size(); i++) {
			writeFloat(f[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(const vector<float>* f) throw (ModelFileIOException) {
		writeInt(f->size());
		for (auto i = 0; i < f->size(); i++) {
			writeFloat((*f)[i]);
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
 * @version $Id$
 */
class tdme::engine::fileio::models::TMWriter
{
public:

	/** 
	 * TDME model format writer
	 * @param model
	 * @param path name
	 * @param file name
	 */
	static void write(Model* model, const string& pathName, const string& fileName) throw (FileSystemException, ModelFileIOException);

private:

	/**
	 * Write material
	 * @param output stream
	 * @param material
	 * @throws model file IO exception
	 */
	static void writeMaterial(TMWriterOutputStream* os, Material* m) throw (ModelFileIOException);

	/** 
	 * Write animation setup
	 * @param output stream
	 * @param animation setup
	 * @throws model file IO exception
	 */
	static void writeAnimationSetup(TMWriterOutputStream* os, AnimationSetup* animationSetup) throw (ModelFileIOException);

	/** 
	 * Write vertices to output stream
	 * @param output stream
	 * @param vertices
	 * @throws model file IO exception
	 */
	static void writeVertices(TMWriterOutputStream* os, vector<Vector3>* v) throw (ModelFileIOException);

	/** 
	 * Write texture coordinates to output stream
	 * @param output stream
	 * @param texture coordinates
	 * @throws model file IO exception
	 */
	static void writeTextureCoordinates(TMWriterOutputStream* os, vector<TextureCoordinate>* tc) throw (ModelFileIOException);

	/** 
	 * Write indices to output stream
	 * @param output stream
	 * @param indices
	 * @throws model file IO exception
	 */
	static void writeIndices(TMWriterOutputStream* os, array<int32_t, 3>* indices) throw (ModelFileIOException);

	/** 
	 * Write animation to output stream
	 * @param output stream
	 * @param animation
	 * @throws model file IO exception
	 */
	static void writeAnimation(TMWriterOutputStream* os, Animation* a) throw (ModelFileIOException);

	/** 
	 * Write faces entities to output stream
	 * @param output stream
	 * @param faces entities
	 * @throws model file IO exception
	 */
	static void writeFacesEntities(TMWriterOutputStream* os, vector<FacesEntity>* facesEntities) throw (ModelFileIOException);

	/** 
	 * Write skinning joint
	 * @param output stream
	 * @param joint
	 * @throws model file IO exception
	 */
	static void writeSkinningJoint(TMWriterOutputStream* os, Joint* joint) throw (ModelFileIOException);

	/** 
	 * Write skinning joint weight
	 * @param output stream
	 * @param joint
	 * @throws model file IO exception
	 */
	static void writeSkinningJointWeight(TMWriterOutputStream* os, JointWeight* jointWeight) throw (ModelFileIOException);

	/** 
	 * Write skinning to output stream
	 * @param output stream
	 * @param skinning
	 * @throws model file IO exception
	 */
	static void writeSkinning(TMWriterOutputStream* os, Skinning* skinning) throw (ModelFileIOException);

	/** 
	 * Write sub groups
	 * @param output stream
	 * @param sub groups
	 * @throws model file IO exception
	 */
	static void writeSubGroups(TMWriterOutputStream* os, map<string, Group*>* subGroups) throw (ModelFileIOException);

	/** 
	 * Write group to output stream
	 * @param output stream
	 * @param group
	 * @throws model file IO exception
	 */
	static void writeGroup(TMWriterOutputStream* os, Group* g) throw (ModelFileIOException);
};
