// Generated from /tdme/src/tdme/engine/fileio/models/TMReader.java

#pragma once

#include <Array.h>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/StringBuffer.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::InputStream;
using java::lang::String;
using java::lang::StringBuffer;
using tdme::engine::model::Animation;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::model::TextureCoordinateArray;
using tdme::math::Vector3Array;

struct default_init_tag;

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
	int8_tArray* data;
	int32_t position;
public:
	/**
	 * Constructor
	 * @param input data array
	 */
	inline TMReaderInputStream(int8_tArray* data) {
		this->data = data;
		this->position = 0;
	}

	/**
	 * Destructor
	 */
	inline ~TMReaderInputStream() {
		delete data;
	}

	/**
	 * Reads a boolean from input stream
	 * @return boolean
	 */
	inline bool readBoolean() {
		return readByte() == 1;
	}

	/**
	 * Reads a byte from input stream
	 * @return byte
	 */
	inline int8_t readByte() {
		return data->get(position++);
	}

	/**
	 * Reads a integer from input stream
	 * @return int
	 */
	inline  int32_t readInt() {
		int32_t value =
			((static_cast< int32_t >(readByte()) & 0xFF) << 24) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 16) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 8)+
			((static_cast< int32_t >(readByte()) & 0xFF) << 0);
		return value;
	}

	/**
	 * Reads a float from input stream
	 * @return float
	 */
	inline float readFloat() {
		int32_t value =
			((static_cast< int32_t >(readByte()) & 0xFF) << 24) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 16) +
			((static_cast< int32_t >(readByte()) & 0xFF) << 8)+
			((static_cast< int32_t >(readByte()) & 0xFF) << 0);
		float* floatValue = (float*)&value;
		return *floatValue;
	}

	/**
	 * Reads a string from input stream
	 * @return string
	 */
	inline String* readString() {
		if (readBoolean() == false) {
			return nullptr;
		} else {
			auto l = readInt();
			auto sb = new StringBuffer();
			for (auto i = 0; i < l; i++) {
				// FIXME: actually we use wide string
				sb->append(static_cast< char16_t >(readByte()));
			}
			return sb->toString();
		}
	}

	/**
	 * Reads a float array from input stream
	 * @return float array
	 */
	inline floatArray* readFloatArray() {
		auto f = new floatArray(readInt());
		for (auto i = 0; i < f->length; i++) {
			(*f)[i] = readFloat();
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
	: public virtual Object
{

public:
	typedef Object super;

	/** 
	 * TDME model format reader
	 * @param path name
	 * @param file name
	 * @throws IOException
	 * @throws ModelIOException
	 * @return model
	 */
	static Model* read(String* pathName, String* fileName) /* throws(IOException, ModelFileIOException) */;

private:

	/** 
	 * Read material
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return material
	 */
	static Material* readMaterial(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read vertices from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return vector3 array
	 */
	static Vector3Array* readVertices(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read texture coordinates from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return texture coordinates array
	 */
	static TextureCoordinateArray* readTextureCoordinates(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read indices from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return indicies / int array
	 */
	static int32_tArray* readIndices(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read animation from input stream into group
	 * @param input stream
	 * @throws IOException 
	 * @throws ModelFileIOException
	 * @return Animation
	 */
	static Animation* readAnimation(TMReaderInputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read faces entities from input stream
	 * @param input stream
	 * @param group
	 * @throws IOException
	 * @throws ModelIOException
	 */
	static void readFacesEntities(TMReaderInputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read skinning joint
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return joint
	 */
	static Joint* readSkinningJoint(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read skinning joint weight
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return joint weight
	 */
	static JointWeight* readSkinningJointWeight(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read skinning from input stream
	 * @param input stream
	 * @param group
	 * @throws IOException
	 */
	static void readSkinning(TMReaderInputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read sub groups
	 * @param input stream
	 * @param model
	 * @param sub groups
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return group
	 */
	static void readSubGroups(TMReaderInputStream* is, Model* model, Group* parentGroup, _HashMap* subGroups) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Write group to output stream
	 * @param input stream
	 * @param model
	 * @param parent group
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return group
	 */
	static Group* readGroup(TMReaderInputStream* is, Model* model, Group* parentGroup) /* throws(IOException, ModelFileIOException) */;

	// Generated

public:
	TMReader();
protected:
	TMReader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
