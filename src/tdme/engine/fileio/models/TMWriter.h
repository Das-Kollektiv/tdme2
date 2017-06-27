// Generated from /tdme/src/tdme/engine/fileio/models/TMWriter.java

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
using tdme::engine::model::FacesEntityArray;
using tdme::engine::model::TextureCoordinateArray;
using tdme::math::Vector3Array;

struct default_init_tag;

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
	 * @throws IOException
	 * @throws ModelIOException
	 */
	static void write(Model* model, String* pathName, String* fileName) /* throws(IOException) */;

private:

	/** 
	 * Writes a boolean to output stream
	 * @param output stream
	 * @param boolean
	 * @throws IOException
	 */
	static void writeBoolean(OutputStream* os, bool b) /* throws(IOException) */;

	/** 
	 * Writes a byte to output stream
	 * @param output stream
	 * @param byte
	 * @throws IOException
	 */
	static void writeByte(OutputStream* os, int8_t b) /* throws(IOException) */;

	/** 
	 * Writes a integer to output stream
	 * @param output stream
	 * @param int
	 * @throws IOException
	 */
	static void writeInt(OutputStream* os, int32_t i) /* throws(IOException) */;

	/** 
	 * Writes a float to output stream
	 * @param output stream
	 * @param float
	 * @throws IOException
	 */
	static void writeFloat(OutputStream* os, float f) /* throws(IOException) */;

	/** 
	 * Writes a string to output stream
	 * @param output stream
	 * @param string
	 * @throws IOException
	 */
	static void writeString(OutputStream* os, String* s) /* throws(IOException) */;

	/** 
	 * Writes a float array to output stream
	 * @param output stream
	 * @param float array
	 * @throws IOException
	 */
	static void writeFloatArray(OutputStream* os, floatArray* f) /* throws(IOException) */;

	/** 
	 * Write material 
	 * @param output stream
	 * @param material
	 * @throws IOException
	 */
	static void writeMaterial(OutputStream* os, Material* m) /* throws(IOException) */;

	/** 
	 * Write vertices to output stream
	 * @param output stream
	 * @param vertices
	 * @throws IOException
	 */
	static void writeVertices(OutputStream* os, Vector3Array* v) /* throws(IOException) */;

	/** 
	 * Write texture coordinates to output stream
	 * @param output stream
	 * @param texture coordinates
	 * @throws IOException
	 */
	static void writeTextureCoordinates(OutputStream* os, TextureCoordinateArray* tc) /* throws(IOException) */;

	/** 
	 * Write indices to output stream
	 * @param output stream
	 * @param indices
	 * @throws IOException
	 */
	static void writeIndices(OutputStream* os, int32_tArray* indices) /* throws(IOException) */;

	/** 
	 * Write animation to output stream
	 * @param output stream
	 * @param animation
	 * @throws IOException 
	 */
	static void writeAnimation(OutputStream* os, Animation* a) /* throws(IOException) */;

	/** 
	 * Write faces entities to output stream
	 * @param output stream
	 * @param faces entities
	 * @throws IOException
	 */
	static void writeFacesEntities(OutputStream* os, FacesEntityArray* facesEntities) /* throws(IOException) */;

	/** 
	 * Write skinning joint
	 * @param output stream
	 * @param joint
	 * @throws IOException
	 */
	static void writeSkinningJoint(OutputStream* os, Joint* joint) /* throws(IOException) */;

	/** 
	 * Write skinning joint weight
	 * @param output stream
	 * @param joint
	 * @throws IOException
	 */
	static void writeSkinningJointWeight(OutputStream* os, JointWeight* jointWeight) /* throws(IOException) */;

	/** 
	 * Write skinning to output stream
	 * @param output stream
	 * @param skinning
	 * @throws IOException
	 */
	static void writeSkinning(OutputStream* os, Skinning* skinning) /* throws(IOException) */;

	/** 
	 * Write sub groups
	 * @param output stream
	 * @param sub groups
	 * @throws IOException
	 */
	static void writeSubGroups(OutputStream* os, _HashMap* subGroups) /* throws(IOException) */;

	/** 
	 * Write group to output stream
	 * @param output stream
	 * @param group
	 * @throws IOException
	 */
	static void writeGroup(OutputStream* os, Group* g) /* throws(IOException) */;

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
