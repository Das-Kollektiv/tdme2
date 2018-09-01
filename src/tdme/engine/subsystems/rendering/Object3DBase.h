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
#include <tdme/engine/subsystems/rendering/AnimationState.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Transformations.h>

using std::map;
using std::vector;
using std::string;

using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::engine::subsystems::rendering::AnimationState;
using tdme::engine::subsystems::rendering::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::math::Matrix4x4;

/** 
 * Object3DInternal base class, contains 
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::Object3DBase
	: public Transformations
{
	friend class Object3DGroup;
	friend class Object3DBase_TransformedFacesIterator;
	friend class ModelUtilitiesInternal;

private:
	Object3DBase_TransformedFacesIterator* transformedFacesIterator {  };

	/**
	 * Determine skinned group count
	 * @param groups groups
	 */
	int32_t determineSkinnedGroupCount(map<string, Group*>* groups); // TODO: std container: maybe use call by reference

	/**
	 * Determine skinned group count
	 * @param map* groups
	 * @param count current count
	 */
	int32_t determineSkinnedGroupCount(map<string, Group*>*, int32_t count); // TODO: std container: maybe use call by reference

	/**
	 * Determine skinned groups
	 * @param map* groups
	 * @param skinningGroups skinning groups
	 * @param idx idx
	 */
	int32_t determineSkinnedGroups(map<string, Group*>*, vector<Group*>& skinningGroups, int32_t idx); // TODO: std container: maybe use call by reference


protected:
	Model* model {  };
	map<string, Matrix4x4*> transformationsMatrices {  };
	bool hasSkinning {  };
	vector<map<string, Matrix4x4*>> skinningGroupsMatrices {  };
	vector<Group*> skinningGroups {  };
	AnimationState baseAnimation {  };
	map<string, AnimationState*> overlayAnimationsById {  };
	map<string, AnimationState*> overlayAnimationsByJointId {  };
	vector<Object3DGroup*> object3dGroups {  };
	bool recreateBuffers {  };
	bool usesMeshManager {  };
	Engine::AnimationProcessingTarget animationProcessingTarget {  };

	/**
	 * Creates all groups transformation matrices
	 * @param matrices matrices
	 * @param groups groups
	 */
	virtual void createTransformationsMatrices(map<string, Matrix4x4*>* matrices, map<string, Group*>* groups); // TODO: std container: maybe use call by reference

	/**
	 * Calculates all groups transformation matrices
	 * @param groups groups
	 * @param parentTransformationsMatrix parent transformations matrix
	 * @param animationState animation state
	 * @param depth depth
	 */
	virtual void computeTransformationsMatrices(map<string, Group*>* groups, Matrix4x4& parentTransformationsMatrix, AnimationState* animationState, int32_t depth); // TODO: std container: maybe use call by reference

	/**
	 * Get skinning groups matrices
	 * @param group group
	 * @return matrices
	 */
	virtual map<string, Matrix4x4*>* getSkinningGroupsMatrices(Group* group);

	/**
	 * Public constructor
	 * @param model model
	 * @param useMeshManager use mesh manager
	 * @param animationProcessingTarget animation processing target
	 */
	Object3DBase(Model* model, bool useMeshManager, Engine::AnimationProcessingTarget animationProcessingTarget);

	/**
	 * Destructor
	 */
	virtual ~Object3DBase();

public:

	/** 
	 * @return model
	 */
	inline virtual Model* getModel() {
		return model;
	}

	/** 
	 * Sets up a base animation to play
	 * @param id id
	 */
	virtual void setAnimation(const string& id);

	/** 
	 * Overlays a animation above the base animation
	 * @param id id
	 */
	virtual void addOverlayAnimation(const string& id);

	/** 
	 * Removes a overlay animation
	 * @param id id
	 */
	virtual void removeOverlayAnimation(const string& id);

	/** 
	 * Removes all finished overlay animations
	 */
	virtual void removeOverlayAnimationsFinished();

	/** 
	 * Removes all overlay animations
	 */
	virtual void removeOverlayAnimations();

	/** 
	 * @return active animation setup id
	 */
	virtual const string getAnimation();

	/** 
	 * Returns current base animation time 
	 * @return 0.0 <= time <= 1.0
	 */
	virtual float getAnimationTime();

	/** 
	 * Returns if there is currently running a overlay animation with given id
	 * @param id id
	 * @return animation is running
	 */
	virtual bool hasOverlayAnimation(const string& id);

	/** 
	 * Returns current overlay animation time
	 * @param id id 
	 * @return 0.0 <= time <= 1.0
	 */
	virtual float getOverlayAnimationTime(const string& id);

	/** 
	 * Returns transformation matrix for given group
	 * @param id group id
	 * @return transformation matrix or null
	 */
	virtual Matrix4x4* getTransformationsMatrix(const string& id);

	/** 
	 * Pre render step, computes transformations
	 */
	virtual void computeTransformations();

	/**
	 * @return group count
	 */
	virtual int getGroupCount() const;

	/** 
	 * Retrieves list of triangles of all or given groups
	 * @param triangles triangles
	 * @param groupIdx group index or -1 for all groups
	 */
	virtual void getTriangles(vector<Triangle>& triangles, int groupIdx = -1);

	/** 
	 * @return transformed faces iterator
	 */
	virtual Object3DBase_TransformedFacesIterator* getTransformedFacesIterator();

	/** 
	 * Returns object3d group mesh object
	 * @param groupId group id
	 * @return object3d group mesh object
	 */
	virtual Object3DGroupMesh* getMesh(const string& groupId);

	/** 
	 * Initiates this object3d 
	 */
	virtual void initialize();

	/** 
	 * Disposes this object3d 
	 */
	virtual void dispose();

	// overriden methods
	virtual const Matrix4x4& getTransformationsMatrix() const;
};
