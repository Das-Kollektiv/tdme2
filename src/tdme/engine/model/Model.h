#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

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
	unordered_map<string, Material*> materials;
	unordered_map<string, Node*> nodes;
	unordered_map<string, Node*> subNodes;
	bool skinning;
	float fps;
	unordered_map<string, AnimationSetup*> animationSetups;
	Matrix4x4 importTransformMatrix;
	unique_ptr<BoundingBox> boundingBox;
	bool boundingBoxUpdated;

	bool embedSpecularTextures;
	bool embedPBRTextures;

	/**
	 * Delete sub nodes
	 * @param subNodes sub nodes
	 */
	void deleteSubNodes(const unordered_map<string, Node*>& subNodes);

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
	 * @returns target node transform
	 */
	bool computeTransformMatrix(const unordered_map<string, Node*>& nodes, const Matrix4x4& parentTransformMatrix, int32_t frame, const string& nodeId, Matrix4x4& transformMatrix);

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
	 * @returns authoring tool
	 */
	inline AuthoringTool getAuthoringTool() {
		return authoringTool;
	}

	/**
	 * @returns unique model id
	 */
	inline uint32_t getUniqueId() {
		return uniqueId;
	}

	/**
	 * @returns model id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * @returns model name
	 */
	inline const string& getName() {
		return name;
	}

	/**
	 * @returns up vector
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
	 * @returns rotation order
	 */
	inline RotationOrder* getRotationOrder() {
		return rotationOrder;
	}

	/**
	 * @returns preferred shader model
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
	 * @returns material ids
	 */
	const vector<string> getMaterialIds();

	/**
	 * Returns all object materials
	 * @returns materials
	 */
	inline unordered_map<string, Material*>& getMaterials() {
		return materials;
	}

	/**
	 * Returns all object's node ids
	 * @returns all node ids
	 */
	const vector<string> getNodeIds();

	/**
	 * Returns all object's nodes
	 * @returns all nodes
	 */
	inline unordered_map<string, Node*>& getNodes() {
		return nodes;
	}

	/**
	 * Returns a node by given name or null
	 * @param id id
	 * @returns
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
	 * @returns sub nodes
	 */
	inline unordered_map<string, Node*>& getSubNodes() {
		return subNodes;
	}

	/**
	 * Returns a sub node by given name or null
	 * @param id id
	 * @returns
	 */
	inline Node* getSubNodeById(const string& id) {
		auto nodeIt = subNodes.find(id);
		if (nodeIt != subNodes.end()) {
			return nodeIt->second;
		}
		return nullptr;
	}

	/**
	 * @returns has skinning
	 */
	inline bool hasSkinning() {
		return skinning;
	}

	/**
	 * @returns frames per seconds
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
	 * @returns animation setups
	 */
	inline const unordered_map<string, AnimationSetup*>& getAnimationSetups() {
		return animationSetups;
	}

	/**
	 * @returns animation setup ids
	 */
	const vector<string> getAnimationSetupIds();

	/**
	 * @returns animation setup for given id or nullptr
	 */
	inline AnimationSetup* getAnimationSetup(const string& id) {
		auto animationSetupIt = animationSetups.find(id);
		if (animationSetupIt != animationSetups.end()) {
			return animationSetupIt->second;
		}
		return nullptr;
	}

	/**
	 * Adds an base animation setup
	 * @param id id
	 * @param startFrame start frame
	 * @param endFrame end frame
	 * @param loop loop
	 * @param speed speed whereas 1.0 is default speed
	 * @returns animation setup
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
	 * @returns animation setup
	 */
	AnimationSetup* addOverlayAnimationSetup(const string& id, const string& overlayFromNodeId, int32_t startFrame, int32_t endFrame, bool loop, float speed = 1.0f);

	/**
	 * Rename animation set up
	 * @param id id
	 * @param newId new id
	 * @returns success
	 */
	bool renameAnimationSetup(const string& id, const string& newId);

	/**
	 * Remove animation setup
	 * @param id id
	 * @returns success
	 */
	bool removeAnimationSetup(const string& id);

	/**
	 * Clear animation setups
	 */
	void clearAnimationSetups();

	/**
	 * @returns if model has animations
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
	 * @returns import transform matrix like converting Z-UP to Y-UP
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
	 * @returns bounding box
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
	 * @returns if vertices have been updated
	 */
	inline bool hasBoundingBoxUpdate() {
		auto updated = boundingBoxUpdated;
		boundingBoxUpdated = false;
		return updated;
	}

	/**
	 * @returns if specular textures will be embedded in model files
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
	 * @returns if PBR textures will be embedded in model files
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
