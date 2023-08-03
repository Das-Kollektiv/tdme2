#pragma once

#include <map>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::unique_ptr;
using std::map;
using std::string;

using std::string;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::ShaderModel;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Matrix4x4;

/**
 * Representation of a 3D model
 * @author andreas.drewke
 */
class tdme::engine::model::Model final
{
	friend class Node;

public:
	enum AuthoringTool {AUTHORINGTOOL_UNKNOWN, AUTHORINGTOOL_BLENDER};

	STATIC_DLL_IMPEXT static string ANIMATIONSETUP_DEFAULT;
	STATIC_DLL_IMPEXT static constexpr float FPS_DEFAULT { 30.0f };
	STATIC_DLL_IMPEXT static uint32_t uidCounter;

private:
	AuthoringTool authoringTool;
	uint32_t uniqueId;
	string id;
	string name;
	UpVector* upVector;
	RotationOrder* rotationOrder;
	ShaderModel* shaderModel;
	map<string, Material*> materials;
	map<string, Node*> nodes;
	map<string, Node*> subNodes;
	bool skinning;
	float fps;
	map<string, AnimationSetup*> animationSetups;
	Matrix4x4 importTransformMatrix;
	unique_ptr<BoundingBox> boundingBox;
	bool boundingBoxUpdated;

	bool embedSpecularTextures;
	bool embedPBRTextures;

	/**
	 * Delete sub nodes
	 * @param subNodes sub nodes
	 */
	void deleteSubNodes(const map<string, Node*>& subNodes);

	/**
	 * Set up if model has skinning
	 * @param hasSkinning has skinning
	 */
	inline void setHasSkinning(bool hasSkinning) {
		skinning = hasSkinning;
	}

	/**
	 * Computes a transform matrix at a given frame for a given node id recursivly
	 * @param nodes nodes
	 * @param parentTransformMatrix parent transform matrix
	 * @param frame frame
	 * @param nodeId node id
	 * @param transformMatrix transform matrix
	 * @return target node transform
	 */
	bool computeTransformMatrix(const map<string, Node*>& nodes, const Matrix4x4& parentTransformMatrix, int32_t frame, const string& nodeId, Matrix4x4& transformMatrix);

public:
	// forbid class copy
	FORBID_CLASS_COPY(Model)

	/**
	 * Public constructor
	 * @param id id
	 * @param name name
	 * @param upVector up vector
	 * @param rotationOrder rotation order
	 * @param boundingBox bounding box
	 * @param authoringTool authoring tool
	 */
	Model(const string& id, const string& name, UpVector* upVector, RotationOrder* rotationOrder, BoundingBox* boundingBox, AuthoringTool authoringTool = AUTHORINGTOOL_UNKNOWN);

	/**
	 * Deconstructor
	 */
	~Model();

	/**
	 * @return authoring tool
	 */
	inline AuthoringTool getAuthoringTool() {
		return authoringTool;
	}

	/**
	 * @return unique model id
	 */
	inline uint32_t getUniqueId() {
		return uniqueId;
	}

	/**
	 * @return model id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * @return model name
	 */
	inline const string& getName() {
		return name;
	}

	/**
	 * @return up vector
	 */
	inline UpVector* getUpVector() {
		return upVector;
	}

	/**
	 * Set up vector
	 * @param upVector up vector
	 */
	inline void setUpVector(UpVector* upVector) {
		this->upVector = upVector;
	}

	/**
	 * @return rotation order
	 */
	inline RotationOrder* getRotationOrder() {
		return rotationOrder;
	}

	/**
	 * @return preferred shader model
	 */
	inline ShaderModel* getShaderModel() {
		return shaderModel;
	}

	/**
	 * Set preferred shader model
	 * @param shaderModel preferred shader model
	 */
	inline void setShaderModel(ShaderModel* shaderModel) {
		this->shaderModel = shaderModel;
	}

	/**
	 * Returns all object materials
	 * @return materials
	 */
	inline map<string, Material*>& getMaterials() {
		return materials;
	}

	/**
	 * Returns all object's nodes
	 * @return all nodes
	 */
	inline map<string, Node*>& getNodes() {
		return nodes;
	}

	/**
	 * Returns a node by given name or null
	 * @param id id
	 * @return
	 */
	inline Node* getNodeById(const string& id) {
		auto nodeIt = nodes.find(id);
		if (nodeIt != nodes.end()) {
			return nodeIt->second;
		}
		return nullptr;
	}

	/**
	 * Returns object's sub nodes
	 * @return sub nodes
	 */
	inline map<string, Node*>& getSubNodes() {
		return subNodes;
	}

	/**
	 * Returns a sub node by given name or null
	 * @param id id
	 * @return
	 */
	inline Node* getSubNodeById(const string& id) {
		auto nodeIt = subNodes.find(id);
		if (nodeIt != subNodes.end()) {
			return nodeIt->second;
		}
		return nullptr;
	}

	/**
	 * @return has skinning
	 */
	inline bool hasSkinning() {
		return skinning;
	}

	/**
	 * @return frames per seconds
	 */
	inline float getFPS() {
		return fps;
	}

	/**
	 * Set model animation frames per seconds
	 * @param fps fps
	 */
	inline void setFPS(float fps) {
		this->fps = fps;
	}

	/**
	 * Adds an base animation setup
	 * @param id id
	 * @param startFrame start frame
	 * @param endFrame end frame
	 * @param loop loop
	 * @param speed speed whereas 1.0 is default speed
	 * @return animation setup
	 */
	AnimationSetup* addAnimationSetup(const string& id, int32_t startFrame, int32_t endFrame, bool loop, float speed = 1.0f);

	/**
	 * Adds an overlay animation setup
	 * @param id id
	 * @param overlayFromNodeId overlay from node id
	 * @param startFrame start frame
	 * @param endFrame end frame
	 * @param loop loop
	 * @param speed speed whereas 1.0 is default speed
	 * @return animation setup
	 */
	AnimationSetup* addOverlayAnimationSetup(const string& id, const string& overlayFromNodeId, int32_t startFrame, int32_t endFrame, bool loop, float speed = 1.0f);

	/**
	 * @return animation setup for given id or null
	 */
	inline AnimationSetup* getAnimationSetup(const string& id) {
		auto animationSetupIt = animationSetups.find(id);
		if (animationSetupIt != animationSetups.end()) {
			return animationSetupIt->second;
		}
		return nullptr;
	}

	/**
	 * Remove animation setup
	 * @param id id
	 * @return success
	 */
	bool removeAnimationSetup(const string& id);

	/**
	 * Rename animation set up
	 * @param id id
	 * @param newId new id
	 * @return success
	 */
	bool renameAnimationSetup(const string& id, const string& newId);

	/**
	 * TODO: return const map
	 * @return animation setup for given id or null
	 */
	inline map<string, AnimationSetup*>& getAnimationSetups() {
		return animationSetups;
	}

	/**
	 * @return if model has animations
	 */
	inline bool hasAnimations() {
		// no registered animation
		if (animationSetups.size() == 0) return false;
		// default animation with frames > 0
		return
			getAnimationSetup(ANIMATIONSETUP_DEFAULT) != nullptr &&
			getAnimationSetup(ANIMATIONSETUP_DEFAULT)->getFrames() > 1;
	}

	/**
	 * @return import transform matrix like converting Z-UP to Y-UP
	 */
	inline const Matrix4x4& getImportTransformMatrix() {
		return importTransformMatrix;
	}

	/**
	 * Set import transform matrix
	 * @param importTransformMatrix import transform matrix like converting Z-UP to Y-UP
	 */
	void setImportTransformMatrix(const Matrix4x4& importTransformMatrix) {
		this->importTransformMatrix = importTransformMatrix;
	}

	/**
	 * @return bounding box
	 */
	BoundingBox* getBoundingBox();

	/**
	 * Invalidates bounding box
	 */
	void invalidateBoundingBox();

	/**
	 * Computes a transform matrix at a given frame for a given node id recursivly
	 * @param nodeId node id
	 * @param parentTransformMatrix parent transform matrix
	 * @param transformMatrix target node transform matrix
	 * @param frame frame or -1 for not using animation data
	 */
	inline bool computeTransformMatrix(const string& nodeId, const Matrix4x4& parentTransformMatrix, Matrix4x4& transformMatrix, int32_t frame = -1) {
		return computeTransformMatrix(subNodes, parentTransformMatrix, frame, nodeId, transformMatrix);
	}

	/**
	 * Computes a transform matrix at a given frame for a given node id recursivly
	 * @param nodeId node id
	 * @param transformMatrix target node transform matrix
	 * @param frame frame
	 */
	inline bool computeTransformMatrix(const string& nodeId, Matrix4x4& transformMatrix, int32_t frame = 0) {
		return computeTransformMatrix(subNodes, importTransformMatrix, frame, nodeId, transformMatrix);
	}

	/**
	 * @return if vertices have been updated
	 */
	inline bool hasBoundingBoxUpdate() {
		auto updated = boundingBoxUpdated;
		boundingBoxUpdated = false;
		return updated;
	}

	/**
	 * @return if specular textures will be embedded in model files
	 */
	inline bool hasEmbeddedSpecularTextures() const {
		return embedSpecularTextures;
	}

	/**
	 * Set if to embed specular textures
	 * @param embedTextures embed specular textures
	 */
	inline void setEmbedSpecularTextures(bool embedTextures) {
		this->embedSpecularTextures = embedTextures;
	}

	/**
	 * @return if PBR textures will be embedded in model files
	 */
	inline bool hasEmbeddedPBRTextures() const {
		return embedPBRTextures;
	}

	/**
	 * Set if to embed PBR textures
	 * @param embedTextures embed PBR textures
	 */
	inline void setEmbedPBRTextures(bool embedTextures) {
		this->embedPBRTextures = embedTextures;
	}

};
