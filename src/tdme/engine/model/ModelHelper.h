
#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::map;
using std::vector;
using std::string;

using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper_VertexOrder;
using tdme::engine::model::Skinning;
using tdme::math::Vector3;

/** 
 * Model Helper
 * @author Andreas Drewke
 */
class tdme::engine::model::ModelHelper final
{

public:
	/** 
	 * Determines vertex order of face
	 * @param vertices
	 * @return vertex order
	 */
	static ModelHelper_VertexOrder* determineVertexOrder(array<Vector3,3>* vertices);

	/** 
	 * Computes face normal for given face vertices
	 * @param face vertices
	 * @param face normal
	 * @return computed face normal
	 */
	static void computeNormal(array<Vector3,3>* vertices, Vector3& normal);

	/** 
	 * Computes face normals for given face vertices
	 * these normals will not be smooth
	 * @param face vertices
	 * @param computed face normals
	 */
	static void computeNormals(array<Vector3,3>* vertices, array<Vector3,3>* normals);

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
	static void prepareForIndexedRendering(map<string, Group*>* groups);

	/** 
	 * Maps original vertices to new vertice mapping
	 * @param skinning
	 * @param vertice mapping / new vertex index to old vertex index
	 * @param vertice count
	 */
	static void prepareForIndexedRendering(Skinning* skinning, vector<int32_t>* vertexMapping, int32_t vertices);

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
};
