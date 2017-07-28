// Generated from /tdme/src/tdme/engine/fileio/models/TMWriter.java

#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <Array.h>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>

using std::array;
using std::map;
using std::vector;
using std::wstring;

using java::lang::Object;
using java::io::OutputStream;
using java::lang::String;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Animation;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;
using tdme::os::_FileSystemException;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using java::lang::String;
using tdme::engine::model::FacesEntityArray;
using tdme::engine::model::TextureCoordinateArray;
using tdme::math::Vector3Array;

struct default_init_tag;

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
	int8_tArray* data;
	int32_t position;
	int32_t capacity;
public:

	/**
	 * Constructor
	 */
	inline TMWriterOutputStream() throw (ModelFileIOException) {
		this->capacity = 1024 * 1024;
		this->data = new (std::nothrow) int8_tArray(capacity);
		if (this->data == nullptr) {
			throw ModelFileIOException("Not enough memory");
		}
		this->position = 0;
	}

	/**
	 * Destructor
	 */
	inline ~TMWriterOutputStream() {
		delete data;
	}

	/**
	 * Get data
	 * @return data
	 */
	inline int8_tArray* getData() {
		return data;
	}

	/**
	 * Get position
	 * @return position
	 */
	inline int32_t getPosition() {
		return position;
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
		if (position + 1 == capacity) {
			this->capacity+= 1024 * 1024;
			int8_tArray* dataNew = new (std::nothrow) int8_tArray(capacity);
			if (dataNew == nullptr) {
				throw ModelFileIOException("Not enough memory");
			}
			for (int i = 0; i < position; i++) {
				dataNew->set(i, data->get(i));
			}
			delete this->data;
			this->data = dataNew;
		}
		data->set(position++, b);
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
	inline void writeString(String* s) throw (ModelFileIOException) {
		if (s == nullptr) {
			writeBoolean(false);
		} else {
			writeBoolean(true);
			writeInt(s->length());
			for (auto i = 0; i < s->length(); i++) {
				// FIXME: actually we use wide string
				writeByte(static_cast< int8_t >(s->charAt(i)));
			}
		}
	}

	/**
	 * Writes a string to output stream
	 * @param string
	 * @throws model file IO exception
	 */
	inline void writeString(const wstring& s) throw (ModelFileIOException) {
		if (s.size() == 0) {
			writeBoolean(false);
		} else {
			writeBoolean(true);
			writeInt(s.size());
			for (auto i = 0; i < s.size(); i++) {
				// FIXME: actually we use wide string
				writeByte(static_cast< int8_t >(s[i]));
			}
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(floatArray* f) throw (ModelFileIOException) {
		writeInt(f->length);
		for (auto i = 0; i < f->length; i++) {
			writeFloat((*f)[i]);
		}
	}

	/**
	 * Writes a float array to output stream
	 * @param float array
	 * @throws model file IO exception
	 */
	inline void writeFloatArray(array<float,2>* f) throw (ModelFileIOException) {
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
	inline void writeFloatArray(array<float,3>* f) throw (ModelFileIOException) {
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
	: public virtual Object
{

public:
	typedef Object super;

	/** 
	 * TDME model format writer
	 * @param model
	 * @param path name
	 * @param file name
	 */
	static void write(Model* model, String* pathName, String* fileName) throw (_FileSystemException, ModelFileIOException);

private:

	/** 
	 * Write material 
	 * @param output stream
	 * @param material
	 * @throws model file IO exception
	 */
	static void writeMaterial(TMWriterOutputStream* os, Material* m) throw (ModelFileIOException);

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
	static void writeSubGroups(TMWriterOutputStream* os, map<wstring, Group*>* subGroups) throw (ModelFileIOException);

	/** 
	 * Write group to output stream
	 * @param output stream
	 * @param group
	 * @throws model file IO exception
	 */
	static void writeGroup(TMWriterOutputStream* os, Group* g) throw (ModelFileIOException);

	// Generated

public:
	TMWriter();
protected:
	TMWriter(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
