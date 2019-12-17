#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>
#include <tdme/math/Matrix2D3x3.h>

using std::string;

using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::FrameBuffer;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Matrix2D3x3;

/** 
 * Object 3D
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::Object3DInternal
	: public Object3DBase
{
	friend class Object3DRenderer;

protected:
	string id;
	bool enabled;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	BoundingBox boundingBox;
	BoundingBox boundingBoxTransformed;

	/**
	 * Update bounding volume
	 */
	inline void updateBoundingBox() {
		boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
		boundingBoxTransformed.getMin().sub(0.05f); // scale a bit up to make picking work better
		boundingBoxTransformed.getMax().add(0.05f); // same here
		boundingBoxTransformed.update();
	}

public:
	/** 
	 * @return object id
	 */
	inline virtual const string& getId() {
		return id;
	}

	/** 
	 * @return true if enabled to be rendered
	 */
	inline virtual bool isEnabled() {
		return enabled;
	}

	/** 
	 * Enable/disable rendering
	 * @param enabled enabled
	 */
	inline virtual void setEnabled(bool enabled) {
		this->enabled = enabled;
	}

	/** 
	 * @return if object is pickable
	 */
	inline virtual bool isPickable() {
		return pickable;
	}

	/** 
	 * Set this object pickable
	 * @param pickable pickable
	 */
	inline virtual void setPickable(bool pickable) {
		this->pickable = pickable;
	}

	/**
	 * @return if entity contributes to shadows
	 */
	inline virtual bool isContributesShadows() {
		return contributesShadows;
	}

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	inline virtual void setContributesShadows(bool contributesShadows) {
		this->contributesShadows = contributesShadows;
	}

	/**
	 * @return if entity receives shadows
	 */
	inline virtual bool isReceivesShadows() {
		return receivesShadows;
	}

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	inline virtual void setReceivesShadows(bool receivesShadows) {
		this->receivesShadows = receivesShadows;
	}

	/** 
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	inline virtual const Color4& getEffectColorMul() const {
		return effectColorMul;
	}

	/** 
	 * The effect color that will be multiplied with fragment color
	 * @param effectColorMul effect color
	 */
	inline virtual void setEffectColorMul(const Color4& effectColorMul) {
		this->effectColorMul = effectColorMul;
	}

	/**
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	inline virtual const Color4& getEffectColorAdd() const {
		return effectColorAdd;
	}

	/**
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	inline virtual void setEffectColorAdd(const Color4& effectColorAdd) {
		this->effectColorAdd = effectColorAdd;
	}

	/** 
	 * @return bounding box
	 */
	inline virtual BoundingBox* getBoundingBox() {
		return &boundingBox;
	}

	/** 
	 * Retrieves bounding sphere with transformations applied
	 * @return bounding sphere
	 */
	inline virtual BoundingBox* getBoundingBoxTransformed() {
		return &boundingBoxTransformed;
	}

	/**
	 * Bind a texture to a group and faces entity
	 * @param textureId texture id
	 * @param groupId group id or empty if texture should be bound to all groups
	 * @param facesEntityId faces entity id or empty if texture should be bound to all faces entities
	 */
	void bindDiffuseTexture(int32_t textureId, const string& groupId = string(), const string& facesEntityId = string());

	/** 
	 * Bind frame buffer color texture to a group and faces entity of this object
	 * @param frameBuffer frame buffer
	 * @param groupId group id or empty string for all
	 * @param facesEntityId faces entity id or empty string for all
	 */
	void bindDiffuseTexture(FrameBuffer* frameBuffer, const string& groupId = string(), const string& facesEntityId = string());

	/** 
	 * Unbind dynamic texture to a group and faces entity of this object
	 * @param groupId group id or empty string for all
	 * @param facesEntityId faces entity id orempty string for all
	 */
	void unbindDiffuseTexture(const string& groupId = string(), const string& facesEntityId = string());

	/**
	 * Set texture matrix
	 * @param textureMatrix texture matrix
	 * @param groupId group id or empty string for all
	 * @param facesEntityId faces entity id or empty string for all
	 */
	virtual void setTextureMatrix(const Matrix2D3x3& textureMatrix, const string& groupId = string(), const string& facesEntityId = string());

	// overriden methods
	inline void initialize() override {
		Object3DBase::initialize();
	}
	inline void dispose() override {
		Object3DBase::dispose();
	}
	void fromTransformations(const Transformations& transformations) override;
	void update() override;
	void setTransformationsMatrix(const string& id, const Matrix4x4& matrix) override;
	void unsetTransformationsMatrix(const string& id) override;

	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 */
	Object3DInternal(const string& id, Model* model);

	/**
	 * Destructor
	 */
	~Object3DInternal();
};
