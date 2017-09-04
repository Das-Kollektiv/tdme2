// Generated from /tdme/src/tdme/engine/fileio/models/TMReader.java

#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>

using std::array;
using std::map;
using std::wstring;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Animation;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;
using tdme::os::_FileSystemException;

namespace tdme {
namespace engine {
namespace fileio {
namespace models {

/**
 * TM reader input stream
 * @author Andreas Drewke
 * @version $Id$
 */
class TMReaderInputStream {
private:
	vector<uint8_t>* data;
	int32_t position;
public:
	/**
	 * Constructor
	 * @param input data array
	 */
	inline TMReaderInputStream(vector<uint8_t>* data) {
		this->data = data;
		this->position = 0;
	}

	/**
	 * Reads a boolean from input stream
	 * @throws model file IO exception
	 * @return boolean
	 */
	inline bool readBoolean() throw (ModelFileIOException) {
		return readByte() == 1;
	}

	/**
	 * Reads a byte from input stream
	 * @throws model file IO exception
	 * @return byte
	 */
	inline int8_t readByte() throw (ModelFileIOException) {
		if (position == data->size()) {
			throw ModelFileIOException("Unexpected end of stream");
		}
		return (*data)[position++];
	}

	/**
	 * Reads a integer from input stream
	 * @throws model file IO exception
	 * @return int
	 */
	inline  int32_t readInt() throw (ModelFileIOException) {
		int32_t value =
			((static_cast< int32_t >(readByte()) & 0xFF) << 24) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 16) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 8) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 0);
		return value;
	}

	/**
	 * Reads a float from input stream
	 * @throws model file IO exception
	 * @return float
	 */
	inline float readFloat() throw (ModelFileIOException) {
		int32_t value =
			((static_cast< int32_t >(readByte()) & 0xFF) << 24) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 16) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 8) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 0);
		float* floatValue = (float*)&value;
		return *floatValue;
	}

	/**
	 * Reads a string from input stream
	 * @throws model file IO exception
	 * @return string
	 */
	inline const wstring readWString() throw (ModelFileIOException) {
		if (readBoolean() == false) {
			return L"";
		} else {
			auto l = readInt();
			wstring s;
			for (auto i = 0; i < l; i++) {
				// FIXME: actually we use wide string
				s+= static_cast< char16_t >(readByte());
			}
			return s;
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws model file IO exception
	 * @return float array
	 */
	inline void readFloatArray(array<float, 16>* data) throw (ModelFileIOException) {
		auto length = readInt();
		if (length != data->size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data->size(); i++) {
			(*data)[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws model file IO exception
	 * @return float array
	 */
	inline void readFloatArray(array<float, 4>* data) throw (ModelFileIOException) {
		auto length = readInt();
		if (length != data->size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data->size(); i++) {
			(*data)[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws model file IO exception
	 * @return float array
	 */
	inline void readFloatArray(array<float, 3>* data) throw (ModelFileIOException) {
		auto length = readInt();
		if (length != data->size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data->size(); i++) {
			(*data)[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws model file IO exception
	 * @return float array
	 */
	inline void readFloatArray(array<float, 2>* data) throw (ModelFileIOException) {
		auto length = readInt();
		if (length != data->size()) {
			throw ModelFileIOException("Wrong float array size");
		}
		for (auto i = 0; i < data->size(); i++) {
			(*data)[i] = readFloat();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @throws model file IO exception
	 * @return float array
	 */
	inline const vector<float> readFloatVector() throw (ModelFileIOException) {
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
 * @version $Id$
 */
class tdme::engine::fileio::models::TMReader
{
public:

	/** 
	 * TDME model format reader
	 * @param path name
	 * @param file name
	 * @throws IOException
	 * @throws model file IO exception
	 * @return model
	 */
	static Model* read(const wstring& pathName, const wstring& fileName) throw (_FileSystemException, ModelFileIOException);

private:

	/** 
	 * Read material
	 * @param input stream
	 * @throws IOException
	 * @throws model file IO exception
	 * @return material
	 */
	static Material* readMaterial(TMReaderInputStream* is) throw (ModelFileIOException);

	/** 
	 * Read vertices from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws model file IO exception
	 * @return vector3 array
	 */
	static const vector<Vector3> readVertices(TMReaderInputStream* is) throw (ModelFileIOException);

	/** 
	 * Read texture coordinates from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws model file IO exception
	 * @return texture coordinates array
	 */
	static const vector<TextureCoordinate> readTextureCoordinates(TMReaderInputStream* is) throw (ModelFileIOException);

	/** 
	 * Read indices from input stream
	 * @param input stream
	 * @param indices
	 * @throws IOException
	 * @throws model file IO exception
	 * @return if having indices
	 */
	static bool readIndices(TMReaderInputStream* is, array<int32_t, 3>* indices) throw (ModelFileIOException);

	/** 
	 * Read animation from input stream into group
	 * @param input stream
	 * @throws IOException 
	 * @throws model file IO exception
	 * @return Animation
	 */
	static Animation* readAnimation(TMReaderInputStream* is, Group* g) throw (ModelFileIOException);

	/** 
	 * Read faces entities from input stream
	 * @param input stream
	 * @param group
	 * @throws model file IO exception
	 */
	static void readFacesEntities(TMReaderInputStream* is, Group* g) throw (ModelFileIOException);

	/** 
	 * Read skinning joint
	 * @param input stream
	 * @throws IOException
	 * @throws model file IO exception
	 * @return joint
	 */
	static Joint readSkinningJoint(TMReaderInputStream* is) throw (ModelFileIOException);

	/** 
	 * Read skinning joint weight
	 * @param input stream
	 * @throws IOException
	 * @throws model file IO exception
	 * @return joint weight
	 */
	static JointWeight readSkinningJointWeight(TMReaderInputStream* is) throw (ModelFileIOException);

	/** 
	 * Read skinning from input stream
	 * @param input stream
	 * @param group
	 * @throws model file IO exception
	 */
	static void readSkinning(TMReaderInputStream* is, Group* g) throw (ModelFileIOException);

	/** 
	 * Read sub groups
	 * @param input stream
	 * @param model
	 * @param sub groups
	 * @throws IOException
	 * @throws model file IO exception
	 * @return group
	 */
	static void readSubGroups(TMReaderInputStream* is, Model* model, Group* parentGroup, map<wstring, Group*>* subGroups) throw (ModelFileIOException);

	/** 
	 * Write group to output stream
	 * @param input stream
	 * @param model
	 * @param parent group
	 * @throws model file IO exception
	 * @return group
	 */
	static Group* readGroup(TMReaderInputStream* is, Model* model, Group* parentGroup) throw (ModelFileIOException);
};
