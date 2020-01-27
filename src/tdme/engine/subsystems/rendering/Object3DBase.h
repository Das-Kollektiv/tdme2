#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DAnimation.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Transformations.h>

using std::map;
using std::vector;
using std::string;

using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::Triangle;
using tdme::engine::subsystems::rendering::Object3DAnimation;
using tdme::engine::subsystems::rendering::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;

/** 
 * Object3D base class
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::Object3DBase: public Transformations, public Object3DAnimation
{
	friend class Object3DGroup;
	friend class Object3DBase_TransformedFacesIterator;
	friend class ModelUtilitiesInternal;

private:
	Object3DBase_TransformedFacesIterator* transformedFacesIterator { nullptr };

protected:
	Model* model;
	vector<Object3DGroup*> object3dGroups;
	bool usesManagers;

	/**
	 * Public constructor
	 * @param model model
	 * @param useManagers use mesh and object 3d group renderer model manager
	 * @param animationProcessingTarget animation processing target
	 */
	Object3DBase(Model* model, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget);

	/**
	 * Destructor
	 */
	virtual ~Object3DBase();

public:

	/** 
	 * @return model
	 */
	inline Model* getModel() {
		return model;
	}

	/**
	 * Pre render step, computes transformations
	 * @param context context
	 * @param lastFrameAtTime time of last animation computation
	 * @param currentFrameAtTime time of current animation computation
	 */
	virtual inline void computeTransformations(void* context, int64_t lastFrameAtTime, int64_t currentFrameAtTime){
		Object3DAnimation::computeTransformations(context, Transformations::getTransformationsMatrix(), lastFrameAtTime, currentFrameAtTime);
		Object3DGroup::computeTransformations(context, object3dGroups);
	} 

	/**
	 * @return group count
	 */
	int getGroupCount() const;

	/** 
	 * Retrieves list of triangles of all or given groups
	 * @param triangles triangles
	 * @param groupIdx group index or -1 for all groups
	 */
	void getTriangles(vector<Triangle>& triangles, int groupIdx = -1);

	/** 
	 * @return transformed faces iterator
	 */
	Object3DBase_TransformedFacesIterator* getTransformedFacesIterator();

	/** 
	 * Returns object3d group mesh object
	 * @param groupId group id
	 * @return object3d group mesh object
	 */
	Object3DGroupMesh* getMesh(const string& groupId);

	/** 
	 * Initiates this object3d 
	 */
	virtual void initialize();

	/** 
	 * Disposes this object3d 
	 */
	virtual void dispose();
};
