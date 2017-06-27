// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DInternal.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/object/Object3DBase.h>

using tdme::engine::subsystems::object::Object3DBase;
using java::lang::String;
using tdme::engine::FrameBuffer;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;


struct default_init_tag;

/** 
 * TDME Object 3D
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DInternal
	: public Object3DBase
{

public:
	typedef Object3DBase super;

public: /* protected */
	String* id {  };
	bool enabled {  };
	bool pickable {  };
	bool dynamicShadowing {  };
	Color4* effectColorMul {  };
	Color4* effectColorAdd {  };
	BoundingBox* boundingBox {  };
	BoundingBox* boundingBoxTransformed {  };
protected:

	/** 
	 * Public constructor
	 * @param model
	 */
	void ctor(String* id, Model* model);

public:

	/** 
	 * @return object id
	 */
	virtual String* getId();

	/** 
	 * @return true if enabled to be rendered
	 */
	virtual bool isEnabled();

	/** 
	 * Enable/disable rendering
	 * @param enabled
	 */
	virtual void setEnabled(bool enabled);

	/** 
	 * @return if object is pickable
	 */
	virtual bool isPickable();

	/** 
	 * Set this object pickable
	 * @param pickable
	 */
	virtual void setPickable(bool pickable);

	/** 
	 * @return dynamic shadowing enabled
	 */
	virtual bool isDynamicShadowingEnabled();

	/** 
	 * Enable/disable dynamic shadowing
	 * @param dynamicShadowing
	 */
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing);

	/** 
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	virtual Color4* getEffectColorMul();

	/** 
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	virtual Color4* getEffectColorAdd();

	/** 
	 * @return bounding box
	 */
	virtual BoundingBox* getBoundingBox();

	/** 
	 * Retrieves bounding sphere with transformations applied
	 * @return bounding sphere
	 */
	virtual BoundingBox* getBoundingBoxTransformed();

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
	virtual void bindDiffuseTexture(String* groupId, FrameBuffer* frameBuffer);

	/** 
	 * Bind frame buffer color texture to a group and faces entity of this object
	 * @param group id
	 * @param faces entity id
	 * @param frame buffer
	 */
	virtual void bindDiffuseTexture(String* groupId, String* facesEntityId, FrameBuffer* frameBuffer);

	/** 
	 * Unbind dynamic texture of this object
	 */
	virtual void unbindDiffuseTexture();

	/** 
	 * Unbind dynamic texture to a group of this object
	 * @param group id
	 */
	virtual void unbindDiffuseTexture(String* groupId);

	/** 
	 * Unbind dynamic texture to a group and faces entity of this object
	 * @param group id
	 * @param faces entity id
	 */
	virtual void unbindDiffuseTexture(String* groupId, String* facesEntityId);

private:

	/** 
	 * Bind a texture to a group and faces entity
	 * @param group id
	 * @param faces entity id or null if texture should be bound to all faces entities
	 * @param texture id
	 */
	void setDynamicDiffuseTexture(String* groupId, String* facesEntityId, int32_t textureId);

public:

	/** 
	 * Initiates this object3d 
	 */
	void initialize() override;

	/** 
	 * Dispose this object3d
	 */
	void dispose() override;
	void fromTransformations(Transformations* transformations) override;
	void update() override;

	// Generated
	Object3DInternal(String* id, Model* model);
protected:
	Object3DInternal(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
