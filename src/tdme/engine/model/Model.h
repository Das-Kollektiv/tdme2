#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;

using std::string;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Group;
using tdme::engine::model::UpVector;
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
	friend class Group;

public:
	enum AuthoringTool {AUTHORINGTOOL_UNKNOWN, AUTHORINGTOOL_BLENDER};

	static string ANIMATIONSETUP_DEFAULT;
	static constexpr float FPS_DEFAULT { 30.0f };

private:
	AuthoringTool authoringTool;
	string id {  };
	string name {  };
	UpVector* upVector {  };
	RotationOrder* rotationOrder {  };
	map<string, Material*> materials {  };
	map<string, Group*> groups {  };
	map<string, Group*> subGroups {  };
	bool hasSkinning_ {  };
	float fps {  };
	map<string, AnimationSetup*> animationSetups {  };
	Matrix4x4 importTransformationsMatrix {  };
	BoundingBox* boundingBox {  };

	/**
	 * Delete sub groups
	 * @param sub groups
	 */
	void deleteSubGroups(map<string, Group*>* subGroups);

	/**
	 * Set up if model has skinning
	 * @param has skinning
	 */
	void setHasSkinning(bool hasSkinning);

	/**
	 * Computes a transformations matrix at a given frame for a given group id recursivly
	 * @param groups
	 * @param parent transformations matrix
	 * @param frame
	 * @param group id
	 * @return target group transformations
	 */
	bool computeTransformationsMatrix(map<string, Group*>* groups, const Matrix4x4& parentTransformationsMatrix, int32_t frame, const string& groupId, Matrix4x4& transformationsMatrix);

public:

	/**
	 * @return authoring tool
	 */
	AuthoringTool getAuthoringTool();

	/** 
	 * @return model id
	 */
	inline const string& getId() {
		return id;
	}

	/** 
	 * @return model name
	 */
	const string& getName();

	/** 
	 * @return up vector
	 */
	UpVector* getUpVector();

	/** 
	 * @return rotation order
	 */
	RotationOrder* getRotationOrder();

	/** 
	 * Returns all object materials
	 * @return materials
	 */
	map<string, Material*>* getMaterials();

	/** 
	 * Returns all object's groups
	 * @return all groups
	 */
	map<string, Group*>* getGroups();

	/** 
	 * Returns a group by given name or null
	 * @param id
	 * @return
	 */
	Group* getGroupById(const string& id);

	/** 
	 * Returns object's sub groups
	 * @return sub groups
	 */
	map<string, Group*>* getSubGroups();

	/** 
	 * Returns a sub group by given name or null
	 * @param id
	 * @return
	 */
	Group* getSubGroupById(const string& id);

	/** 
	 * @return has skinning
	 */
	bool hasSkinning();

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
	AnimationSetup* addAnimationSetup(const string& id, int32_t startFrame, int32_t endFrame, bool loop);

	/** 
	 * Adds an overlay animation setup
	 * @param id
	 * @param overlay from group id
	 * @param start frame
	 * @param end frame
	 * @param loop
	 * @return animation setup
	 */
	AnimationSetup* addOverlayAnimationSetup(const string& id, const string& overlayFromGroupId, int32_t startFrame, int32_t endFrame, bool loop);

	/** 
	 * @return animation setup for given id or null
	 */
	AnimationSetup* getAnimationSetup(const string& id);

	/** 
	 * @return animation setup for given id or null
	 */
	map<string, AnimationSetup*>* getAnimationSetups();

	/** 
	 * @return if model has animations
	 */
	bool hasAnimations();

	/** 
	 * @return import transformations matrix like converting Z-UP to Y-UP
	 */
	Matrix4x4& getImportTransformationsMatrix();

	/** 
	 * @return bounding box
	 */
	BoundingBox* getBoundingBox();

	/**
	 * Computes a transformations matrix at a given frame for a given group id recursivly
	 * @param group id
	 * @param parent transformations matrix
	 * @param target group transformations matrix
	 * @param frame
	 */
	bool computeTransformationsMatrix(const string& groupId, const Matrix4x4& parentTransformationsMatrix, Matrix4x4& transformationsMatrix, int32_t frame = 0);

	/**
	 * Computes a transformations matrix at a given frame for a given group id recursivly
	 * @param group id
	 * @param target group transformations matrix
	 * @param frame
	 */
	bool computeTransformationsMatrix(const string& groupId, Matrix4x4& transformationsMatrix, int32_t frame = 0);

	/**
	 * Public constructor
	 * @param id
	 * @param name
	 * @param up vector
	 * @param rotation order
	 * @param bounding box
	 * @param authoring tool
	 */
	Model(const string& id, const string& name, UpVector* upVector, RotationOrder* rotationOrder, BoundingBox* boundingBox, AuthoringTool authoringTool = AUTHORINGTOOL_UNKNOWN);

	/**
	 * Deconstructor
	 */
	~Model();
};
