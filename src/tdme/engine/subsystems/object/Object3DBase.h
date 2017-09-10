// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DBase.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/object/AnimationState.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Transformations.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::engine::subsystems::object::AnimationState;
using tdme::engine::subsystems::object::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::math::Matrix4x4;

/** 
 * Object3DInternal base class, contains 
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::object::Object3DBase
	: public Transformations
{

public: /* protected */
	Model* model {  };
	map<wstring, Matrix4x4*> transformationsMatrices {  };
	Matrix4x4* tmpMatrix1 {  };
	bool hasSkinning {  };
	vector<map<wstring, Matrix4x4*>> skinningGroupsMatrices {  };
	vector<Group*> skinningGroups {  };
	AnimationState baseAnimation {  };
	map<wstring, AnimationState*> overlayAnimationsById {  };
	map<wstring, AnimationState*> overlayAnimationsByJointId {  };
	vector<Object3DGroup*> object3dGroups {  };
	bool recreateBuffers {  };
	bool usesMeshManager {  };
	Engine::AnimationProcessingTarget animationProcessingTarget {  };

private:
	Object3DBase_TransformedFacesIterator* transformedFacesIterator {  };

public:

	/** 
	 * @return model
	 */
	virtual Model* getModel();

	/** 
	 * Sets up a base animation to play
	 * @param id
	 */
	virtual void setAnimation(const wstring& id);

	/** 
	 * Overlays a animation above the base animation
	 * @param id
	 */
	virtual void addOverlayAnimation(const wstring& id);

	/** 
	 * Removes a overlay animation
	 * @param id
	 */
	virtual void removeOverlayAnimation(const wstring& id);

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
	virtual const wstring getAnimation();

	/** 
	 * Returns current base animation time 
	 * @return 0.0 <= time <= 1.0
	 */
	virtual float getAnimationTime();

	/** 
	 * Returns if there is currently running a overlay animation with given id
	 * @param id
	 * @return animation is running
	 */
	virtual bool hasOverlayAnimation(const wstring& id);

	/** 
	 * Returns current overlay animation time
	 * @param id 
	 * @return 0.0 <= time <= 1.0
	 */
	virtual float getOverlayAnimationTime(const wstring& id);

	/** 
	 * Returns transformation matrix for given group
	 * @param group id
	 * @return transformation matrix or null
	 */
	virtual Matrix4x4* getTransformationsMatrix(const wstring& id);

public: /* protected */

	/** 
	 * Creates all groups transformation matrices
	 * @param matrices
	 * @param groups
	 */
	virtual void createTransformationsMatrices(map<wstring, Matrix4x4*>* matrices, map<wstring, Group*>* groups);

	/** 
	 * Calculates all groups transformation matrices
	 * @param groups
	 * @param parent transformations matrix
	 * @param animation state
	 * @param depth
	 */
	virtual void computeTransformationsMatrices(map<wstring, Group*>* groups, Matrix4x4* parentTransformationsMatrix, AnimationState* animationState, int32_t depth);

public:

	/** 
	 * Pre render step, computes transformations
	 */
	virtual void computeTransformations();

	/** 
	 * Retrieves complete list of face triangles for all render groups
	 * TODO: 
	 * these are untransformed, so even without group transformation, check later if this makes really sense in all cases
	 * as it is working with physics test 1 + 3 I currently leave it as it is
	 * @param face triangles
	 */
	virtual void getFaceTriangles(vector<Triangle>* faceTriangles);

	/** 
	 * @return transformed faces iterator
	 */
	virtual Object3DBase_TransformedFacesIterator* getTransformedFacesIterator();

	/** 
	 * Returns object3d group mesh object
	 * @param group id
	 * @return object3d group mesh object
	 */
	virtual Object3DGroupMesh* getMesh(const wstring& groupId);

private:

	/** 
	 * Determine skinned group count
	 * @param groups
	 * @param current count
	 */
	int32_t determineSkinnedGroupCount(map<wstring, Group*>* groups);

	/** 
	 * Determine skinned group count
	 * @param groups
	 * @param current count
	 */
	int32_t determineSkinnedGroupCount(map<wstring, Group*>*, int32_t count);

	/** 
	 * Determine skinned groups
	 * @param groups
	 * @param skinning groups
	 * @param idx
	 */
	int32_t determineSkinnedGroups(map<wstring, Group*>*, vector<Group*>* skinningGroups, int32_t idx);

public: /* protected */

	/** 
	 * Get skinning groups matrices
	 * @param group
	 * @return matrices
	 */
	virtual map<wstring, Matrix4x4*>* getSkinningGroupsMatrices(Group* group);

public:

	/** 
	 * Initiates this object3d 
	 */
	virtual void initialize();

	/** 
	 * Disposes this object3d 
	 */
	virtual void dispose();

	// Generated

public: /* protected */
	/**
	 * Public constructor
	 * @param model
	 * @param use mesh manager
	 * @param animation processing target
	 */
	Object3DBase(Model* model, bool useMeshManager, Engine::AnimationProcessingTarget animationProcessingTarget);

public:
	virtual Matrix4x4* getTransformationsMatrix();

private:
	friend class Object3DBase_TransformedFacesIterator;
};
