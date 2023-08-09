#pragma once

#include <map>
#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ModelStatistics.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::unordered_map;

using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::rendering::ModelStatistics;
using tdme::engine::subsystems::rendering::ObjectModelInternal;
using tdme::math::Matrix4x4;

/**
 * Model utilities
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ModelUtilitiesInternal
{
public:
	/**
	 * Creates a bounding box from given model
	 * @param model model
	 * @param overriddenNodeTransformMatrices overridden node transform matrices
	 * @return axis aligned bounding box
	 */
	static BoundingBox* createBoundingBox(Model* model, const unordered_map<string, Matrix4x4*> overriddenNodeTransformMatrices = unordered_map<string, Matrix4x4*>());

	/**
	 * Invert normals of a model
	 * @param model model
	 */
	static void invertNormals(Model* model);

	/**
	 * Compute model statistics
	 * @param model model
	 * @param modelStatistics model statistics
	 */
	static void computeModelStatistics(Model* model, ModelStatistics* modelStatistics);

	/**
	 * Compute model statistics
	 * @param objectModelInternal object model internal
	 * @param modelStatistics model statistics
	 */
	static void computeModelStatistics(ObjectModelInternal* objectModelInternal, ModelStatistics* modelStatistics);

	/**
	 * Compute if model 1 equals model 2
	 * @param model1 model 1
	 * @param model2 model 2
	 * @return model1 equals model2
	 */
	static bool equals(Model* model1, Model* model2);

	/**
	 * Compute if model 1 equals model 2
	 * @param objectModel1Internal model 1
	 * @param objectModel2Internal model 2
	 * @return model1 equals model2
	 */
	static bool equals(ObjectModelInternal* objectModel1Internal, ObjectModelInternal* objectModel2Internal);

private:
	/**
	 * Creates a bounding box from given object model
	 * @param objectModelInternal model
	 * @return axis aligned bounding box
	 */
	static BoundingBox* createBoundingBox(ObjectModelInternal* objectModelInternal);

	/**
	 * Creates a bounding box from given object model without mesh
	 * @param objectModelInternal model
	 * @return boundingBox axis aligned bounding box
	 */
	static BoundingBox* createBoundingBoxNoMesh(ObjectModelInternal* objectModelInternal);

	/**
	 * Invert normals recursive
	 * @param nodes nodes
	 */
	static void invertNormals(const map<string, Node*>& nodes);

};
