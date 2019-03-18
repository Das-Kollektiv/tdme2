#pragma once

#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/ObjectParticleSystemInternal.h>
#include <tdme/engine/Entity.h>

using std::vector;
using std::string;

using tdme::engine::subsystems::particlesystem::ObjectParticleSystemInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Object particle system entity to be used with engine class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::ObjectParticleSystem final
	: public ObjectParticleSystemInternal
	, public Entity
{
private:
	bool frustumCulling { true };
	Entity* parentEntity { nullptr };

public:
	/**
	 * Set parent entity, needs to be called before adding to engine
	 * @param entity entity
	 */
	inline void setParentEntity(Entity* entity) {
		this->parentEntity = entity;
	}

	/**
	 * @return parent entity
	 */
	inline Entity* getParentEntity() {
		return parentEntity;
	}

	// overriden methods
	void initialize() override;

	inline BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	inline BoundingBox* getBoundingBoxTransformed() override {
		return &boundingBoxTransformed;
	}

	/** 
	 * @return enabled objects
	 */
	inline const vector<Object3D*>& getEnabledObjects() {
		return enabledObjects;
	}

	// overriden methods
	void fromTransformations(const Transformations& transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	void updateParticles() override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;
	void setAutoEmit(bool autoEmit) override;

	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 * @param scale scale
	 * @param autoEmit auto emit
	 * @param enableDynamicShadows enable dynamic shadows
	 * @param maxCount max count
	 * @param emitter emitter
	 */
	ObjectParticleSystem(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter);

public:

	// overriden methods
	virtual void dispose() override;
	virtual void setEngine(Engine* engine) override;
	virtual void setRenderer(GLRenderer* renderer) override;

	inline virtual const Color4& getEffectColorAdd() const override {
		return ObjectParticleSystemInternal::getEffectColorAdd();
	}

	inline virtual void setEffectColorAdd(const Color4& effectColorAdd) override {
		ObjectParticleSystemInternal::setEffectColorAdd(effectColorAdd);
	}

	inline virtual const Color4& getEffectColorMul() const override {
		return ObjectParticleSystemInternal::getEffectColorMul();
	}

	inline virtual void setEffectColorMul(const Color4& effectColorMul) override {
		ObjectParticleSystemInternal::setEffectColorMul(effectColorMul);
	}

	inline virtual const string& getId() override {
		return ObjectParticleSystemInternal::getId();
	}

	inline virtual bool isDynamicShadowingEnabled() override {
		return ObjectParticleSystemInternal::isDynamicShadowingEnabled();
	}

	inline virtual bool isEnabled() override {
		return ObjectParticleSystemInternal::isEnabled();
	}

	inline virtual bool isPickable() override {
		return ObjectParticleSystemInternal::isPickable();
	}

	inline virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		ObjectParticleSystemInternal::setDynamicShadowingEnabled(dynamicShadowing);
	}

	inline virtual void setPickable(bool pickable) override {
		ObjectParticleSystemInternal::setPickable(pickable);
	}

	inline virtual const Vector3& getTranslation() const override {
		return Transformations::getTranslation();
	}

	inline virtual void setTranslation(const Vector3& translation) override {
		Transformations::setTranslation(translation);
	}

	inline virtual const Vector3& getScale() const override {
		return Transformations::getScale();
	}

	inline virtual void setScale(const Vector3& scale) override {
		Transformations::setScale(scale);
	}

	inline virtual const Vector3& getPivot() const override {
		return Transformations::getPivot();
	}

	inline virtual void setPivot(const Vector3& pivot) override {
		Transformations::setPivot(pivot);
	}

	inline virtual const int getRotationCount() const override {
		return Transformations::getRotationCount();
	}

	inline virtual Rotation& getRotation(const int idx) override {
		return Transformations::getRotation(idx);
	}

	inline virtual void addRotation(const Vector3& axis, const float angle) override {
		Transformations::addRotation(axis, angle);
	}

	inline virtual void removeRotation(const int idx) override {
		Transformations::removeRotation(idx);
	}

	inline virtual const Vector3& getRotationAxis(const int idx) const override {
		return Transformations::getRotationAxis(idx);
	}

	inline virtual void setRotationAxis(const int idx, const Vector3& axis) override {
		Transformations::setRotationAxis(idx, axis);
	}

	inline virtual const float getRotationAngle(const int idx) const override {
		return Transformations::getRotationAngle(idx);
	}

	inline virtual void setRotationAngle(const int idx, const float angle) override {
		Transformations::setRotationAngle(idx, angle);
	}

	inline virtual const Quaternion& getRotationsQuaternion() const override {
		return Transformations::getRotationsQuaternion();
	}

	inline virtual const Matrix4x4& getTransformationsMatrix() const override {
		return Transformations::getTransformationsMatrix();
	}

	inline virtual const Transformations& getTransformations() const override {
		return *this;
	}

};
