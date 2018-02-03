#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/object/Object3DInternal.h>
#include <tdme/engine/Entity.h>

using std::string;

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
	Engine* engine { nullptr };
	bool frustumCulling { true };
public:
	void setEngine(Engine* engine) override;
	void setRenderer(GLRenderer* renderer) override;
	void fromTransformations(Transformations* transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;

	/**
	 * Public constructor
	 * @param id
	 * @param model
	 */
	Object3D(const string& id, Model* model);

public:
	virtual void dispose() override;
	virtual BoundingBox* getBoundingBox() override;
	virtual BoundingBox* getBoundingBoxTransformed() override;
	virtual Color4& getEffectColorAdd() override;
	virtual Color4& getEffectColorMul() override;
	virtual const string& getId() override;
	virtual Vector3& getPivot() override;
	virtual Rotations* getRotations() override;
	virtual Vector3& getScale() override;
	virtual Matrix4x4& getTransformationsMatrix() override;
	virtual Vector3& getTranslation() override;
	virtual void initialize() override;
	virtual bool isDynamicShadowingEnabled() override;
	virtual bool isEnabled() override;
	virtual bool isPickable() override;
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override;
	virtual void setPickable(bool pickable) override;
	virtual Matrix4x4* getTransformationsMatrix(const string& id) override;
};
