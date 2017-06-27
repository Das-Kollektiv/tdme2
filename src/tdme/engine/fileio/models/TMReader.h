// Generated from /tdme/src/tdme/engine/fileio/models/TMReader.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::InputStream;
using java::lang::String;
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
	 * Reads a boolean from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return boolean
	 */
	static bool readBoolean(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Reads a byte from input stream
	 * @param output stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return byte
	 */
	static int8_t readByte(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Reads a integer from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return int
	 */
	static int32_t readInt(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Reads a float from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelIOException
	 * @return float
	 */
	static float readFloat(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Reads a string from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return string
	 */
	static String* readString(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Reads a float array from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return float array
	 */
	static floatArray* readFloatArray(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read material
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return material
	 */
	static Material* readMaterial(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read vertices from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return vector3 array
	 */
	static Vector3Array* readVertices(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read texture coordinates from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return texture coordinates array
	 */
	static TextureCoordinateArray* readTextureCoordinates(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read indices from input stream
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return indicies / int array
	 */
	static int32_tArray* readIndices(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read animation from input stream into group
	 * @param input stream
	 * @throws IOException 
	 * @throws ModelFileIOException
	 * @return Animation
	 */
	static Animation* readAnimation(InputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read faces entities from input stream
	 * @param input stream
	 * @param group
	 * @throws IOException
	 * @throws ModelIOException
	 */
	static void readFacesEntities(InputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read skinning joint
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return joint
	 */
	static Joint* readSkinningJoint(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read skinning joint weight
	 * @param input stream
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return joint weight
	 */
	static JointWeight* readSkinningJointWeight(InputStream* is) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read skinning from input stream
	 * @param input stream
	 * @param group
	 * @throws IOException
	 */
	static void readSkinning(InputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Read sub groups
	 * @param input stream
	 * @param model
	 * @param sub groups
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return group
	 */
	static void readSubGroups(InputStream* is, Model* model, Group* parentGroup, _HashMap* subGroups) /* throws(IOException, ModelFileIOException) */;

	/** 
	 * Write group to output stream
	 * @param input stream
	 * @param model
	 * @param parent group
	 * @throws IOException
	 * @throws ModelFileIOException
	 * @return group
	 */
	static Group* readGroup(InputStream* is, Model* model, Group* parentGroup) /* throws(IOException, ModelFileIOException) */;

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
