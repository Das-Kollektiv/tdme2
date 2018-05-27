#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>

using std::string;

using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::FrameBuffer;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;

/** 
 * TDME Object 3D
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::Object3DInternal
	: public Object3DBase
{
	friend class Object3DVBORenderer;

protected:
	string id {  };
	bool enabled {  };
	bool pickable {  };
	bool dynamicShadowing {  };
	Color4 effectColorMul {  };
	Color4 effectColorAdd {  };
	BoundingBox* boundingBox {  };
	BoundingBox* boundingBoxTransformed {  };

	/**
	 * Bind a texture to a group and faces entity
	 * @param group id
	 * @param faces entity id or null if texture should be bound to all faces entities
	 * @param texture id
	 */
	void setDynamicDiffuseTexture(const string& groupId, const string& facesEntityId, int32_t textureId);

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
	 * @param enabled
	 */
	virtual void setEnabled(bool enabled);

	/** 
	 * @return if object is pickable
	 */
	inline virtual bool isPickable() {
		return pickable;
	}

	/** 
	 * Set this object pickable
	 * @param pickable
	 */
	virtual void setPickable(bool pickable);

	/** 
	 * @return dynamic shadowing enabled
	 */
	inline virtual bool isDynamicShadowingEnabled() {
		return dynamicShadowing;
	}

	/** 
	 * Enable/disable dynamic shadowing
	 * @param dynamicShadowing
	 */
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing);

	/** 
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	inline virtual const Color4& getEffectColorMul() const {
		return effectColorMul;
	}

	/** 
	 * The effect color that will be multiplied with fragment color
	 * @param effect color
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
		return boundingBox;
	}

	/** 
	 * Retrieves bounding sphere with transformations applied
	 * @return bounding sphere
	 */
	inline virtual BoundingBox* getBoundingBoxTransformed() {
		return boundingBoxTransformed;
	}

	/** 
	 * Bind frame buffer color texture to this object
	 * @param group id
	 * @param faces entity name or null if texture should be bound to all faces entities
	 * @param frame buffer
	 */
	virtual void bindDiffuseTexture(FrameBuffer* frameBuffer);

	/** 
	 * Bind frame buffer color texture to a group of this object
	 * @param group id
	 * @param faces entity name or null if texture should be bound to all faces entities
	 * @param frame buffer
	 */
	virtual void bindDiffuseTexture(const string& groupId, FrameBuffer* frameBuffer);

	/** 
	 * Bind frame buffer color texture to a group and faces entity of this object
	 * @param group id
	 * @param faces entity id
	 * @param frame buffer
	 */
	virtual void bindDiffuseTexture(const string& groupId, const string& facesEntityId, FrameBuffer* frameBuffer);

	/** 
	 * Unbind dynamic texture of this object
	 */
	virtual void unbindDiffuseTexture();

	/** 
	 * Unbind dynamic texture to a group of this object
	 * @param group id
	 */
	virtual void unbindDiffuseTexture(const string& groupId);

	/** 
	 * Unbind dynamic texture to a group and faces entity of this object
	 * @param group id
	 * @param faces entity id
	 */
	virtual void unbindDiffuseTexture(const string& groupId, const string& facesEntityId);

	// overriden methods
	void initialize() override;
	void dispose() override;
	void fromTransformations(const Transformations& transformations) override;
	void update() override;

	/**
	 * Public constructor
	 * @param id
	 * @param model
	 */
	Object3DInternal(const string& id, Model* model);

	/**
	 * Destructor
	 */
	~Object3DInternal();
};
