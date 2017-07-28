// Generated from /tdme/src/tdme/engine/model/Model.java

#pragma once

#include <map>
#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::wstring;

using std::wstring;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Group;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Matrix4x4;

/** 
 * Represents a 3d model
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Model final
{

public:
	static wstring ANIMATIONSETUP_DEFAULT;
	static constexpr float FPS_DEFAULT { 30.0f };

private:
	wstring id {  };
	wstring name {  };
	Model_UpVector* upVector {  };
	RotationOrder* rotationOrder {  };
	map<wstring, Material*> materials {  };
	map<wstring, Group*> groups {  };
	map<wstring, Group*> subGroups {  };
	bool hasSkinning_ {  };
	float fps {  };
	map<wstring, AnimationSetup*> animationSetups {  };
	Matrix4x4 importTransformationsMatrix {  };
	BoundingBox* boundingBox {  };
public:

	/** 
	 * @return model id
	 */
	const wstring& getId();

	/** 
	 * @return model name
	 */
	const wstring& getName();

	/** 
	 * @return up vector
	 */
	Model_UpVector* getUpVector();

	/** 
	 * @return rotation order
	 */
	RotationOrder* getRotationOrder();

	/** 
	 * Returns all object materials
	 * @return materials
	 */
	map<wstring, Material*>* getMaterials();

	/** 
	 * Returns all object's groups
	 * @return all groups
	 */
	map<wstring, Group*>* getGroups();

	/** 
	 * Returns a group by given name or null
	 * @param id
	 * @return
	 */
	Group* getGroupById(const wstring& id);

	/** 
	 * Returns object's sub groups
	 * @return sub groups
	 */
	map<wstring, Group*>* getSubGroups();

	/** 
	 * Returns a sub group by given name or null
	 * @param id
	 * @return
	 */
	Group* getSubGroupById(const wstring& id);

	/** 
	 * @return has skinning
	 */
	bool hasSkinning();

public: /* protected */

	/** 
	 * Set up if model has skinning
	 * @param has skinning
	 */
	void setHasSkinning(bool hasSkinning);

public:

	/** 
	 * @return frames per seconds
	 */
	float getFPS();

	/** 
	 * Set model animation frames per seconds
	 * @param fps
	 */
	void setFPS(float fps);

	/** 
	 * Adds an base animation setup
	 * @param id
	 * @param start frame
	 * @param end frame
	 * @param loop
	 * @return animation setup
	 */
	AnimationSetup* addAnimationSetup(const wstring& id, int32_t startFrame, int32_t endFrame, bool loop);

	/** 
	 * Adds an overlay animation setup
	 * @param id
	 * @param overlay from group id
	 * @param start frame
	 * @param end frame
	 * @param loop
	 * @return animation setup
	 */
	AnimationSetup* addOverlayAnimationSetup(const wstring& id, const wstring& overlayFromGroupId, int32_t startFrame, int32_t endFrame, bool loop);

	/** 
	 * @return animation setup for given id or null
	 */
	AnimationSetup* getAnimationSetup(const wstring& id);

	/** 
	 * @return animation setup for given id or null
	 */
	map<wstring, AnimationSetup*>* getAnimationSetups();

	/** 
	 * @return if model has animations
	 */
	bool hasAnimations();

	/** 
	 * @return import transformations matrix like converting Z-UP to Y-UP
	 */
	Matrix4x4* getImportTransformationsMatrix();

	/** 
	 * @return bounding box
	 */
	BoundingBox* getBoundingBox();

	/** 
	 * Computes a transformations matrix for a given frame and group id
	 * @param frame
	 * @param group id
	 * @return group transformations matrix or null
	 */
	Matrix4x4* computeTransformationsMatrix(int32_t frame, const wstring& groupId);

public: /* protected */

	/** 
	 * Computes a transformations matrix at a given frame for a given group id recursivly
	 * @param groups
	 * @param parent transformations matrix
	 * @param frame
	 * @param group id
	 * @return group transformations matrix or null
	 */
	Matrix4x4* computeTransformationsMatrix(map<wstring, Group*>* groups, Matrix4x4* parentTransformationsMatrix, int32_t frame, const wstring& groupId);

	/**
	 * Public constructor
	 * @param id
	 * @param name
	 * @param up vector
	 * @param rotation order
	 * @param bounding box
	 */
	Model(const wstring& id, const wstring& name, Model_UpVector* upVector, RotationOrder* rotationOrder, BoundingBox* boundingBox);
};
