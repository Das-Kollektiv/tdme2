#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DInternal.h>
#include <tdme/engine/Entity.h>

using std::string;

using tdme::engine::subsystems::rendering::Object3DInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
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
	void fromTransformations(const Transformations& transformations) override;
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
	// overriden methods
	virtual void dispose() override;

	inline virtual BoundingBox* getBoundingBox() override {
		return Object3DInternal::getBoundingBox();
	}

	inline virtual BoundingBox* getBoundingBoxTransformed() override {
		return Object3DInternal::getBoundingBoxTransformed();
	}

	inline virtual Color4& getEffectColorAdd() override {
		return Object3DInternal::getEffectColorAdd();
	}

	inline virtual Color4& getEffectColorMul() override {
		return Object3DInternal::getEffectColorMul();
	}

	inline virtual const string& getId() override {
		return Object3DInternal::getId();
	}

	virtual void initialize() override;

	inline virtual bool isDynamicShadowingEnabled() override {
		return Object3DInternal::isDynamicShadowingEnabled();
	}

	inline virtual bool isEnabled() override {
		return Object3DInternal::isEnabled();
	}

	inline virtual bool isPickable() override {
		return Object3DInternal::isPickable();
	}

	virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override;
	virtual void setPickable(bool pickable) override;
	virtual Matrix4x4* getTransformationsMatrix(const string& id) override;
	virtual const Vector3& getTranslation() const override;
	virtual void setTranslation(const Vector3& translation) override;
	virtual const Vector3& getScale() const override;
	virtual void setScale(const Vector3& scale) override;
	virtual const Vector3& getPivot() const override;
	virtual void setPivot(const Vector3& pivot) override;
	virtual const int getRotationCount() const override;
	virtual Rotation& getRotation(const int idx) override;
	virtual void addRotation(const Vector3& axis, const float angle) override;
	virtual void removeRotation(const int idx) override;
	virtual const Vector3& getRotationAxis(const int idx) const override;
	virtual void setRotationAxis(const int idx, const Vector3& axis) override;
	virtual const float getRotationAngle(const int idx) const override;
	virtual void setRotationAngle(const int idx, const float angle) override;
	virtual const Quaternion& getRotationsQuaternion() const override;

	inline virtual const Matrix4x4& getTransformationsMatrix() const override {
		return Transformations::getTransformationsMatrix();
	}

	inline virtual const Transformations& getTransformations() const override {
		return *this;
	}
};
