// Generated from /tdme/src/tdme/engine/Object3D.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/object/Object3DInternal.h>
#include <tdme/engine/Entity.h>

using tdme::engine::subsystems::object::Object3DInternal;
using tdme::engine::Entity;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Object 3D
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Object3D final
	: public Object3DInternal
	, public Entity
{

public:
	typedef Object3DInternal super;

private:
	Engine* engine {  };
protected:

	/** 
	 * Public constructor
	 * @param id
	 * @param model
	 */
	void ctor(String* id, Model* model);

public:
	void setEngine(Engine* engine) override;
	void setRenderer(GLRenderer* renderer) override;
	void fromTransformations(Transformations* transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;

	// Generated
	Object3D(String* id, Model* model);
protected:
	Object3D(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual void dispose();
	virtual BoundingBox* getBoundingBox();
	virtual BoundingBox* getBoundingBoxTransformed();
	virtual Color4* getEffectColorAdd();
	virtual Color4* getEffectColorMul();
	virtual String* getId();
	virtual Vector3* getPivot();
	virtual Rotations* getRotations();
	virtual Vector3* getScale();
	virtual Matrix4x4* getTransformationsMatrix();
	virtual Vector3* getTranslation();
	virtual void initialize();
	virtual bool isDynamicShadowingEnabled();
	virtual bool isEnabled();
	virtual bool isPickable();
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing);
	virtual void setPickable(bool pickable);
	virtual Matrix4x4* getTransformationsMatrix(String* id);

private:
	virtual ::java::lang::Class* getClass0();
};
