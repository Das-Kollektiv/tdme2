// Generated from /tdme/src/tdme/engine/model/ModelHelper.java

#pragma once

#include <map>
#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::map;
using std::wstring;

using java::lang::Object;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper_VertexOrder;
using tdme::engine::model::Skinning;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Model Helper
 * @author Andreas Drewke
 */
class tdme::engine::model::ModelHelper final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Determines vertex order of face
	 * @param vertices
	 * @return vertex order
	 */
	static ModelHelper_VertexOrder* determineVertexOrder(Vector3Array* vertices);

	/** 
	 * Computes face normal for given face vertices
	 * @param face vertices
	 * @return face normal
	 */
	static Vector3* computeNormal(Vector3Array* vertices);

	/** 
	 * Computes face normals for given face vertices
	 * these normals will not be smooth
	 * @param face vertices
	 * @return face normals
	 */
	static Vector3Array* computeNormals(Vector3Array* vertices);

	/** 
	 * Create normal tangents and bitangents for groups with normal mapping
	 * @see http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
	 * @param group
	 */
	static void createNormalTangentsAndBitangents(Group* group);

	/** 
	 * Prepare for indexed rendering
	 * @param model
	 */
	static void prepareForIndexedRendering(Model* model);

private:

	/** 
	 * Prepares this group for indexed rendering
	 * @param groups
	 */
	static void prepareForIndexedRendering(map<wstring, Group*>* groups);

	/** 
	 * Maps original vertices to new vertice mapping
	 * @param skinning
	 * @param vertice mapping / new vertex index to old vertex index
	 * @param vertice count
	 */
	static void prepareForIndexedRendering(Skinning* skinning, int32_tArray* vertexMapping, int32_t vertices);

public:

	/** 
	 * Set up joints for skinning groups
	 * @param model
	 */
	static void setupJoints(Model* model);

private:

	/** 
	 * Sets up a group as joint taking all subgroups into account
	 * @param group
	 */
	static void setJoint(Group* root);

public:

	/** 
	 * Fix animation length
	 * @param model
	 */
	static void fixAnimationLength(Model* model);

private:

	/** 
	 * Fixes animation length as sometimes they are only given partially, which is not supported by engine
	 * @param group
	 * @param frames
	 */
	static void fixAnimationLength(Group* root, int32_t frames);

public:

	/** 
	 * Create default animation
	 * @param model
	 * @param frames
	 */
	static void createDefaultAnimation(Model* model, int32_t frames);

	// Generated
	ModelHelper();
protected:
	ModelHelper(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class ModelHelper_VertexOrder;
};
