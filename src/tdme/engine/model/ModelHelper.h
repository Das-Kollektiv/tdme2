#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::map;
using std::vector;
using std::string;

using tdme::engine::Transformations;
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
	 * @param vertices vertices
	 * @return vertex order
	 */
	static ModelHelper_VertexOrder* determineVertexOrder(const vector<Vector3>& vertices);

	/** 
	 * Computes face normal for given face vertices
	 * @param vertices face vertices
	 * @param normal face normal
	 * @return computed face normal
	 */
	static void computeNormal(const array<Vector3,3>& vertices, Vector3& normal);

	/** 
	 * Computes face normals for given face vertices
	 * these normals will not be smooth
	 * @param vertices face vertices
	 * @param normals computed face normals
	 */
	static void computeNormals(const array<Vector3,3>& vertices, array<Vector3,3>& normals);

	/** 
	 * Create normal tangents and bitangents for groups with normal mapping
	 * @see http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
	 * @param group group
	 */
	static void createNormalTangentsAndBitangents(Group* group);

	/** 
	 * Prepare for indexed rendering
	 * @param model model
	 */
	static void prepareForIndexedRendering(Model* model);

	/**
	 * Set diffuse masked transparency for given model
	 * @param model model
	 * @param maskedTransparency masked transparency
	 */
	static void setDiffuseMaskedTransparency(Model* model, bool maskedTransparency);
private:

	/** 
	 * Prepares this group for indexed rendering
	 * @param groups groups
	 */
	static void prepareForIndexedRendering(map<string, Group*>* groups); // TODO: std container: maybe use call by reference

	/** 
	 * Maps original vertices to new vertice mapping
	 * @param skinning skinning
	 * @param vertexMapping vertice mapping / new vertex index to old vertex index
	 * @param vertices vertice count
	 */
	static void prepareForIndexedRendering(Skinning* skinning, const vector<int32_t>& vertexMapping, int32_t vertices);

public:

	/** 
	 * Set up joints for skinning groups
	 * @param model model
	 */
	static void setupJoints(Model* model);

private:

	/** 
	 * Sets up a group as joint taking all subgroups into account
	 * @param root group
	 */
	static void setJoint(Group* root);

public:

	/** 
	 * Fix animation length
	 * @param model model
	 */
	static void fixAnimationLength(Model* model);

private:

	/** 
	 * Fixes animation length as sometimes they are only given partially, which is not supported by engine
	 * @param root group
	 * @param frames frames
	 */
	static void fixAnimationLength(Group* root, int32_t frames);

public:

	/** 
	 * Check default animation
	 * @param model model
	 * @return if animation exists
	 */
	static bool hasDefaultAnimation(Model* model);

	/**
	 * Create default animation
	 * @param model model
	 * @param frames frames
	 */
	static void createDefaultAnimation(Model* model, int32_t frames);

	/**
	 * Clone material
	 * @param material material
	 * @return material
	 */
	static Material* cloneMaterial(Material* material);

	/**
	 * Create model from source sub groups into target sub groups
	 * @param sourceGroup source group
	 * @param targetModel target model
	 * @param targetParentGroup target parent group
	 */
	static void cloneGroup(Group* sourceGroup, Model* targetModel, Group* targetParentGroup = nullptr);

private:

	/**
	 * Partition sub groups
	 * @param sourceGroup source group to partition
	 * @param modelsByPartition models by partition
	 * @param modelsPosition models position
	 * @param parentTransformationsMatrix parent transformations matrix
	 */
	static void partitionGroup(Group* sourceGroup, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition, const Matrix4x4& parentTransformationsMatrix);

	/**
	 * Shrink to fit group
	 * @param group group
	 */
	static void shrinkToFit(Group* group);

	/**
	 * Compute normals
	 * @param group group
	 */
	static void computeNormals(Group* group);

public:
	/**
	 * Partition model
	 * @param model model
	 * @param transformations transformations
	 * @param modelsByPartition models by partition
	 * @param modelsPosition models position
	 */
	static void partition(Model* model, const Transformations& transformations, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition);

	/**
	 * Shrink to fit
	 * @param model model
	 */
	static void shrinkToFit(Model* model);

	/**
	 * Compute normals
	 * @param group group
	 */
	static void computeNormals(Model* model);

};
