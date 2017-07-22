// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DBase.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Transformations.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::Transformations;
using java::lang::String;
using tdme::engine::Engine_AnimationProcessingTarget;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::engine::subsystems::object::AnimationState;
using tdme::engine::subsystems::object::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::math::Matrix4x4;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Group, ::java::lang::ObjectArray > GroupArray;
}  // namespace model

namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::BoundingVolume, ::java::lang::ObjectArray > BoundingVolumeArray;
typedef ::SubArray< ::tdme::engine::primitives::Triangle, ::java::lang::ObjectArray, BoundingVolumeArray > TriangleArray;
}  // namespace primitives

namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DGroup, ::java::lang::ObjectArray > Object3DGroupArray;
}  // namespace object
}  // namespace subsystems
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::model::GroupArray;
using tdme::engine::primitives::BoundingVolumeArray;
using tdme::engine::primitives::TriangleArray;
using tdme::engine::subsystems::object::Object3DGroupArray;
using tdme::math::Matrix4x4Array;

struct default_init_tag;

/** 
 * Object3DInternal base class, contains 
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::object::Object3DBase
	: public Transformations
{

public:
	typedef Transformations super;

public: /* protected */
	Model* model {  };
	map<wstring, Matrix4x4*> transformationsMatrices {  };
	Matrix4x4* parentTransformationsMatrix {  };
	Matrix4x4* transformationsMatrix {  };
	vector<Matrix4x4*> transformationsMatricesStack {  };
	Matrix4x4* tmpMatrix1 {  };
	bool hasSkinning {  };
	vector<map<wstring, Matrix4x4*>> skinningGroupsMatrices {  };
	GroupArray* skinningGroups {  };
	AnimationState* baseAnimation {  };
	map<wstring, AnimationState*> overlayAnimationsById {  };
	map<wstring, AnimationState*> overlayAnimationsByJointId {  };
	Object3DGroupArray* object3dGroups {  };
	bool recreateBuffers {  };
	bool usesMeshManager {  };
	Engine_AnimationProcessingTarget* animationProcessingTarget {  };

private:
	Object3DBase_TransformedFacesIterator* transformedFacesIterator {  };
protected:

	/** 
	 * Public constructor
	 * @param model
	 */
	void ctor(Model* model, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget);

public:

	/** 
	 * @return model
	 */
	virtual Model* getModel();

	/** 
	 * Sets up a base animation to play
	 * @param id
	 */
	virtual void setAnimation(String* id);

	/** 
	 * Overlays a animation above the base animation
	 * @param id
	 */
	virtual void addOverlayAnimation(String* id);

	/** 
	 * Removes a overlay animation
	 * @param id
	 */
	virtual void removeOverlayAnimation(String* id);

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
	virtual String* getAnimation();

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
	virtual bool hasOverlayAnimation(String* id);

	/** 
	 * Returns current overlay animation time
	 * @param id 
	 * @return 0.0 <= time <= 1.0
	 */
	virtual float getOverlayAnimationTime(String* id);

	/** 
	 * Returns transformation matrix for given group
	 * @param group id
	 * @return transformation matrix or null
	 */
	virtual Matrix4x4* getTransformationsMatrix(String* id);

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

	/** 
	 * Calculates all groups transformation matrices
	 * @param groups
	 * @param depth
	 */
	virtual int32_t determineTransformationsMatricesStackDepth(map<wstring, Group*>* groups, int32_t depth);

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
	 * @return faces
	 */
	virtual TriangleArray* getFaceTriangles();

	/** 
	 * @return transformed faces iterator
	 */
	virtual Object3DBase_TransformedFacesIterator* getTransformedFacesIterator();

	/** 
	 * Returns object3d group mesh object
	 * @param group id
	 * @return object3d group mesh object
	 */
	virtual Object3DGroupMesh* getMesh(String* groupId);

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
	int32_t determineSkinnedGroups(map<wstring, Group*>*, GroupArray* skinningGroups, int32_t idx);

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
	Object3DBase(Model* model, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget);
protected:
	Object3DBase(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();

public:
	virtual Matrix4x4* getTransformationsMatrix();

private:
	virtual ::java::lang::Class* getClass0();
	friend class Object3DBase_TransformedFacesIterator;
};
