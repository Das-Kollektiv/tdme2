#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectAnimation.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/math/Matrix2D3x3.h>

using std::string;

using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::rendering::ObjectAnimation;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::ColorTexture;
using tdme::engine::FrameBuffer;
using tdme::engine::Transform;
using tdme::math::Matrix2D3x3;

/**
 * Object
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectInternal
	: public ObjectBase
{
	friend class EntityRenderer;

protected:
	string id;
	bool enabled;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	BoundingBox boundingBox;
	BoundingBox worldBoundingBox;
	bool nodeTransformMatrixUpdate;

	/**
	 * Update bounding volume
	 */
	void updateBoundingBox();

	/**
	 * Set parent transform
	 * @param parentTransform parent transform
	 */
	inline void setParentTransform(const Transform& parentTransform) {
		ObjectBase::setParentTransform(parentTransform);
		updateBoundingBox();
	}

public:
	// forbid class copy
	CLASS_FORBID_COPY(ObjectInternal)

	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 * @param instances instances to compute and render by duplication
	 */
	ObjectInternal(const string& id, Model* model, int instances);

	/**
	 * Destructor
	 */
	virtual ~ObjectInternal();

	/**
	 * @return object id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * @return true if enabled to be rendered
	 */
	inline bool isEnabled() {
		return enabled;
	}

	/**
	 * Enable/disable rendering
	 * @param enabled enabled
	 */
	inline void setEnabled(bool enabled) {
		this->enabled = enabled;
	}

	/**
	 * @return if object is pickable
	 */
	inline bool isPickable() {
		return pickable;
	}

	/**
	 * Set this object pickable
	 * @param pickable pickable
	 */
	inline void setPickable(bool pickable) {
		this->pickable = pickable;
	}

	/**
	 * @return if entity contributes to shadows
	 */
	inline bool isContributesShadows() {
		return contributesShadows;
	}

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	inline void setContributesShadows(bool contributesShadows) {
		this->contributesShadows = contributesShadows;
	}

	/**
	 * @return if entity receives shadows
	 */
	inline bool isReceivesShadows() {
		return receivesShadows;
	}

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	inline void setReceivesShadows(bool receivesShadows) {
		this->receivesShadows = receivesShadows;
	}

	/**
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	inline const Color4& getEffectColorMul() const {
		return effectColorMul;
	}

	/**
	 * The effect color that will be multiplied with fragment color
	 * @param effectColorMul effect color
	 */
	inline void setEffectColorMul(const Color4& effectColorMul) {
		this->effectColorMul = effectColorMul;
	}

	/**
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	inline const Color4& getEffectColorAdd() const {
		return effectColorAdd;
	}

	/**
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	inline void setEffectColorAdd(const Color4& effectColorAdd) {
		this->effectColorAdd = effectColorAdd;
	}

	/**
	 * @return bounding box
	 */
	inline BoundingBox* getBoundingBox() {
		return &boundingBox;
	}

	/**
	 * Retrieves world bounding box
	 * @return world bounding box
	 */
	inline BoundingBox* getWorldBoundingBox() {
		return &worldBoundingBox;
	}

	/**
	 * Bind a texture to a node and faces entity
	 * @param textureId texture id
	 * @param nodeId node id or empty if texture should be bound to all nodes
	 * @param facesEntityId faces entity id or empty if texture should be bound to all faces entities
	 */
	void bindDiffuseTexture(int32_t textureId, const string& nodeId = string(), const string& facesEntityId = string());

	/**
	 * Bind frame buffer color texture to a node and faces entity of this object
	 * @param frameBuffer frame buffer
	 * @param nodeId node id or empty string for all
	 * @param facesEntityId faces entity id or empty string for all
	 */
	void bindDiffuseTexture(ColorTexture* texture, const string& nodeId = string(), const string& facesEntityId = string());

	/**
	 * Unbind dynamic texture to a node and faces entity of this object
	 * @param nodeId node id or empty string for all
	 * @param facesEntityId faces entity id orempty string for all
	 */
	void unbindDiffuseTexture(const string& nodeId = string(), const string& facesEntityId = string());

	/**
	 * Set texture matrix
	 * @param textureMatrix texture matrix
	 * @param nodeId node id or empty string for all
	 * @param facesEntityId faces entity id or empty string for all
	 */
	void setTextureMatrix(const Matrix2D3x3& textureMatrix, const string& nodeId = string(), const string& facesEntityId = string());

	// overridden methods
	inline void initialize() override {
		ObjectBase::initialize();
	}
	inline void dispose() override {
		ObjectBase::dispose();
	}
	void setTransform(const Transform& transform);
	void update();

	/**
	 * Set node transform matrix
	 * @param id id
	 * @param matrix matrix
	 */
	void setNodeTransformMatrix(const string& id, const Matrix4x4& matrix);

	/**
	 * Unset node transform matrix
	 * @param id id
	 */
	void unsetNodeTransformMatrix(const string& id);

};
