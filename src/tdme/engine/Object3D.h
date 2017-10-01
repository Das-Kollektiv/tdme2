// Generated from /tdme/src/tdme/engine/Object3D.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/object/Object3DInternal.h>
#include <tdme/engine/Entity.h>

using std::wstring;

using tdme::engine::subsystems::object::Object3DInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Object 3D
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Object3D final
	: public Object3DInternal
	, public Entity
{

private:
	Engine* engine {  };
public:
	void setEngine(Engine* engine) override;
	void setRenderer(GLRenderer* renderer) override;
	void fromTransformations(Transformations* transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;

	/**
	 * Public constructor
	 * @param id
	 * @param model
	 */
	Object3D(const wstring& id, Model* model);
public:
	virtual void dispose();
	virtual BoundingBox* getBoundingBox();
	virtual BoundingBox* getBoundingBoxTransformed();
	virtual Color4* getEffectColorAdd();
	virtual Color4* getEffectColorMul();
	virtual const wstring& getId();
	virtual Vector3& getPivot();
	virtual Rotations* getRotations();
	virtual Vector3& getScale();
	virtual Matrix4x4& getTransformationsMatrix();
	virtual Vector3& getTranslation();
	virtual void initialize();
	virtual bool isDynamicShadowingEnabled();
	virtual bool isEnabled();
	virtual bool isPickable();
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing);
	virtual void setPickable(bool pickable);
	virtual Matrix4x4* getTransformationsMatrix(const wstring& id);
};
