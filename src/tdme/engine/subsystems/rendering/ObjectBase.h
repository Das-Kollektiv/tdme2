#pragma once

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectAnimation.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>

using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::primitives::Triangle;
using tdme::engine::subsystems::rendering::ObjectAnimation;
using tdme::engine::subsystems::rendering::ObjectBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;

/**
 * Object base class
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectBase
{
	friend class ObjectNode;
	friend class ObjectNodeMesh;
	friend class ObjectBase_TransformedFacesIterator;
	friend class ModelUtilitiesInternal;
	friend class tdme::engine::subsystems::skinning::SkinningShader;

private:
	unique_ptr<ObjectBase_TransformedFacesIterator> transformedFacesIterator;

protected:
	Model* model;
	vector<ObjectNode*> objectNodes;
	bool usesManagers;
	int instances;
	int enabledInstances;
	vector<ObjectAnimation*> instanceAnimations;
	vector<bool> instanceEnabled;
	vector<Transform> instanceTransform;
	int currentInstance;
	Engine::AnimationProcessingTarget animationProcessingTarget;
	Transform parentTransform;
	mutable Matrix4x4 currentTransformMatrix;

	// forbid class copy
	FORBID_CLASS_COPY(ObjectBase)

	/**
	 * Set parent transform
	 * @param parentTransform parent transform
	 */
	inline void setParentTransform(const Transform& parentTransform) {
		this->parentTransform = parentTransform;
	}

	/**
	 * Private constructor
	 * @param model model
	 * @param useManagers use mesh manager
	 * @param animationProcessingTarget animation processing target
	 * @param instances instances to compute and render by duplication
	 */
	ObjectBase(Model* model, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, int instances);

	/**
	 * Destructor
	 */
	virtual ~ObjectBase();

public:

	/**
	 * @returns model
	 */
	inline Model* getModel() {
		return model;
	}

	/**
	 * Compute animation
	 * @param contextIdx context index
	 * @param lastFrameAtTime time of last animation computation
	 * @param currentFrameAtTime time of current animation computation
	 */
	virtual inline void computeAnimation(int contextIdx, int64_t lastFrameAtTime, int64_t currentFrameAtTime){
		enabledInstances = 0;
		for (auto i = 0; i < instances; i++) {
			if (instanceEnabled[i] == false) continue;
			instanceAnimations[i]->computeAnimation(contextIdx, instanceTransform[i].getTransformMatrix(), lastFrameAtTime, currentFrameAtTime);
			enabledInstances++;
		}
		if (enabledInstances > 0) ObjectNode::computeAnimation(contextIdx, objectNodes);
	}

	/**
	 * @returns node count
	 */
	int getNodeCount() const;

	/**
	 * Retrieves list of triangles of all or given nodes
	 * @param triangles triangles
	 * @param nodeIdx node index or -1 for all nodes
	 */
	void getTriangles(vector<Triangle>& triangles, int nodeIdx = -1);

	/**
	 * @returns transformed faces iterator
	 */
	ObjectBase_TransformedFacesIterator* getTransformedFacesIterator();

	/**
	 * Returns object node mesh object
	 * @param nodeId node id
	 * @returns object node mesh object
	 */
	ObjectNodeMesh* getMesh(const string& nodeId);

	/**
	 * Initiates this object
	 */
	virtual void initialize();

	/**
	 * Disposes this object
	 */
	virtual void dispose();

	/**
	 * @returns maximum of instances
	 */
	inline int getInstances() {
		return instances;
	}

	/**
	 * @returns current instance
	 */
	inline int getCurrentInstance() {
		return currentInstance;
	}

	/**
	 * Set current instance
	 * @param current instance
	 */
	inline void setCurrentInstance(int currentInstance) {
		if (currentInstance >= 0 && currentInstance < instances) this->currentInstance = currentInstance;
	}

	/**
	 * @returns current instance enabled
	 */
	inline bool getInstanceEnabled() {
		return instanceEnabled[currentInstance];
	}

	/**
	 * Set current instance enabled
	 * @param enabled instance enabled
	 */
	inline void setInstanceEnabled(bool enabled) {
		instanceEnabled[currentInstance] = enabled;
	}

	/**
	 * Sets up a base animation to play
	 * @param id id
	 * @param speed speed whereas 1.0 is default speed
	 */
	inline void setAnimation(const string& id, float speed = 1.0f) {
		instanceAnimations[currentInstance]->setAnimation(id, speed);
	}

	/**
	 * Set up animation speed
	 * @param speed speed whereas 1.0 is default speed
	 */
	inline void setAnimationSpeed(float speed) {
		instanceAnimations[currentInstance]->setAnimationSpeed(speed);
	}

	/**
	 * Overlays a animation above the base animation
	 * @param id id
	 */
	inline void addOverlayAnimation(const string& id) {
		instanceAnimations[currentInstance]->addOverlayAnimation(id);
	}

	/**
	 * Removes a overlay animation
	 * @param id id
	 */
	inline void removeOverlayAnimation(const string& id) {
		instanceAnimations[currentInstance]->removeOverlayAnimation(id);
	}

	/**
	 * Removes all finished overlay animations
	 */
	inline void removeFinishedOverlayAnimations() {
		instanceAnimations[currentInstance]->removeFinishedOverlayAnimations();
	}

	/**
	 * Removes all overlay animations
	 */
	inline void removeOverlayAnimations() {
		instanceAnimations[currentInstance]->removeOverlayAnimations();
	}

	/**
	 * @returns active animation setup id
	 */
	inline const string getAnimation() {
		return instanceAnimations[currentInstance]->getAnimation();
	}

	/**
	 * Returns current base animation time
	 * @returns 0.0 <= time <= 1.0
	 */
	inline float getAnimationTime() {
		return instanceAnimations[currentInstance]->getAnimationTime();
	}

	/**
	 * Returns if there is currently running a overlay animation with given id
	 * @param id id
	 * @returns animation is running
	 */
	inline bool hasOverlayAnimation(const string& id) {
		return instanceAnimations[currentInstance]->hasOverlayAnimation(id);
	}

	/**
	 * Returns current overlay animation time
	 * @param id id
	 * @returns 0.0 <= time <= 1.0
	 */
	inline float getOverlayAnimationTime(const string& id) {
		return instanceAnimations[currentInstance]->getOverlayAnimationTime(id);
	}

	/**
	 * Returns transform matrix for given node
	 * @param id node id
	 * @returns transform matrix or identity matrix if not found
	 */
	inline const Matrix4x4 getNodeTransformMatrix(const string& id) {
		return instanceAnimations[currentInstance]->getNodeTransformMatrix(id);
	}

	/**
	 * Set transform matrix for given node
	 * @param id node id
	 * @param matrix transform matrix
	 */
	inline void setNodeTransformMatrix(const string& id, const Matrix4x4& matrix) {
		instanceAnimations[currentInstance]->setNodeTransformMatrix(id, matrix);
	}

	/**
	 * Unset transform matrix for given node
	 * @param id node id
	 */
	inline void unsetNodeTransformMatrix(const string& id) {
		instanceAnimations[currentInstance]->unsetNodeTransformMatrix(id);
	}

	/**
	 * @returns this transform matrix
	 */
	inline const Matrix4x4& getTransformMatrix() const {
		return currentTransformMatrix.set((parentTransform * instanceTransform[currentInstance]).getTransformMatrix());
	}

};
