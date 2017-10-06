
#pragma once

#include <map>
#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/object/ModelStatistics.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::wstring;

using tdme::engine::model::Model;
using tdme::engine::model::Group;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::ModelStatistics;
using tdme::engine::subsystems::object::Object3DModelInternal;

/** 
 * Model utilities
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::ModelUtilitiesInternal
{
public:
	/** 
	 * Creates a bounding box from given model
	 * @param model
	 * @return axis aligned bounding box
	 */
	static BoundingBox* createBoundingBox(Model* model);

	/** 
	 * Creates a bounding box from given object3d model
	 * @param model
	 * @return axis aligned bounding box
	 */
	static BoundingBox* createBoundingBox(Object3DModelInternal* object3DModelInternal);

	/** 
	 * Invert normals of a model
	 * @param model
	 */
	static void invertNormals(Model* model);

private:

	/** 
	 * Invert normals recursive
	 * @param groups
	 */
	static void invertNormals(map<wstring, Group*>* groups);

public:

	/** 
	 * Compute model statistics
	 * @param model
	 * @param model statistics
	 */
	static void computeModelStatistics(Model* model, ModelStatistics* modelStatistics);

	/** 
	 * Compute model statistics
	 * @param object 3d model internal
	 * @param model statistics
	 */
	static void computeModelStatistics(Object3DModelInternal* object3DModelInternal, ModelStatistics* modelStatistics);

	/** 
	 * Compute if model 1 equals model 2
	 * @param model 1
	 * @param model 2
	 * @return model1 equals model2
	 */
	static bool equals(Model* model1, Model* model2);

	/** 
	 * Compute if model 1 equals model 2
	 * @param model 1
	 * @param model 2
	 * @return model1 equals model2
	 */
	static bool equals(Object3DModelInternal* object3DModel1Internal, Object3DModelInternal* object3DModel2Internal);
};
