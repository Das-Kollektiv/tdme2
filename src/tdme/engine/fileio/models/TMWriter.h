// Generated from /tdme/src/tdme/engine/fileio/models/TMWriter.java

#pragma once

#include <Array.h>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>

using java::lang::Object;
using java::io::OutputStream;
using java::lang::String;
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
using tdme::utils::_HashMap;

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
	inline TMWriterOutputStream() {
		this->capacity = 1024 * 1024;
		this->data = new int8_tArray(capacity);
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
	 * @param boolean
	 */
	inline void writeBoolean(bool b) {
		writeByte(b == true?1:0);
	}

	/**
	 * Writes a byte to output stream
	 * @param byte
	 */
	inline void writeByte(int8_t b) {
		if (position + 1 == capacity) {
			this->capacity+= 1024 * 1024;
			int8_tArray* dataNew = new int8_tArray(capacity);
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
	 * @param int
	 */
	inline void writeInt(int32_t i) {
		writeByte((i >> 24) & 0xFF);
		writeByte((i >> 16) & 0xFF);
		writeByte((i >> 8) & 0xFF);
		writeByte((i >> 0) & 0xFF);
	}

	/**
	 * Writes a float to output stream
	 * @param float
	 */
	inline void writeFloat(float f) {
		int value = *((int*)&f);
		writeInt(value);
	}

	/**
	 * Writes a string to output stream
	 * @param string
	 */
	inline void writeString(String* s) {
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
	 * Writes a float array to output stream
	 * @param float array
	 */
	inline void writeFloatArray(floatArray* f) {
		writeInt(f->length);
		for (auto i = 0; i < f->length; i++) {
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
	static void write(Model* model, String* pathName, String* fileName) /* throws(IOException) */;

private:

	/** 
	 * Write material 
	 * @param output stream
	 * @param material
	 */
	static void writeMaterial(TMWriterOutputStream* os, Material* m) /* throws(IOException) */;

	/** 
	 * Write vertices to output stream
	 * @param output stream
	 * @param vertices
	 */
	static void writeVertices(TMWriterOutputStream* os, Vector3Array* v) /* throws(IOException) */;

	/** 
	 * Write texture coordinates to output stream
	 * @param output stream
	 * @param texture coordinates
	 */
	static void writeTextureCoordinates(TMWriterOutputStream* os, TextureCoordinateArray* tc) /* throws(IOException) */;

	/** 
	 * Write indices to output stream
	 * @param output stream
	 * @param indices
	 */
	static void writeIndices(TMWriterOutputStream* os, int32_tArray* indices) /* throws(IOException) */;

	/** 
	 * Write animation to output stream
	 * @param output stream
	 * @param animation
	 */
	static void writeAnimation(TMWriterOutputStream* os, Animation* a) /* throws(IOException) */;

	/** 
	 * Write faces entities to output stream
	 * @param output stream
	 * @param faces entities
	 */
	static void writeFacesEntities(TMWriterOutputStream* os, FacesEntityArray* facesEntities) /* throws(IOException) */;

	/** 
	 * Write skinning joint
	 * @param output stream
	 * @param joint
	 */
	static void writeSkinningJoint(TMWriterOutputStream* os, Joint* joint) /* throws(IOException) */;

	/** 
	 * Write skinning joint weight
	 * @param output stream
	 * @param joint
	 */
	static void writeSkinningJointWeight(TMWriterOutputStream* os, JointWeight* jointWeight) /* throws(IOException) */;

	/** 
	 * Write skinning to output stream
	 * @param output stream
	 * @param skinning
	 */
	static void writeSkinning(TMWriterOutputStream* os, Skinning* skinning) /* throws(IOException) */;

	/** 
	 * Write sub groups
	 * @param output stream
	 * @param sub groups
	 */
	static void writeSubGroups(TMWriterOutputStream* os, _HashMap* subGroups) /* throws(IOException) */;

	/** 
	 * Write group to output stream
	 * @param output stream
	 * @param group
	 */
	static void writeGroup(TMWriterOutputStream* os, Group* g) /* throws(IOException) */;

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
