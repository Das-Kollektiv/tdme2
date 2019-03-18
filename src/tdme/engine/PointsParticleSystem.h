#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemInternal.h>
#include <tdme/engine/Entity.h>

using std::string;

using tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Point particle system entity to be used with engine class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::PointsParticleSystem final
	: public PointsParticleSystemInternal
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
	 * @param emitter emitter
	 * @param maxPoints max points
	 * @param pointSize point size
	 * @param autoEmit auto emit
	 * @param texture texture
	 */
	PointsParticleSystem(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, bool autoEmit, Texture* texture = nullptr);
public:
	// overridden methods
	virtual void setEngine(Engine* engine) override;
	virtual void setRenderer(GLRenderer* renderer) override;
	virtual void dispose() override;

	inline virtual const Color4& getEffectColorAdd() const override {
		return PointsParticleSystemInternal::getEffectColorAdd();
	}

	inline virtual void setEffectColorAdd(const Color4& effectColorAdd) override {
		PointsParticleSystemInternal::setEffectColorAdd(effectColorAdd);
	}

	inline virtual const Color4& getEffectColorMul() const override {
		return PointsParticleSystemInternal::getEffectColorMul();
	}

	inline virtual void setEffectColorMul(const Color4& effectColorMul) override {
		PointsParticleSystemInternal::setEffectColorMul(effectColorMul);
	}

	inline virtual const string& getId() override {
		return PointsParticleSystemInternal::getId();
	}

	inline virtual bool isDynamicShadowingEnabled() override {
		return PointsParticleSystemInternal::isDynamicShadowingEnabled();
	}

	inline virtual bool isEnabled() override {
		return PointsParticleSystemInternal::isEnabled();
	}

	inline virtual bool isPickable() override {
		return PointsParticleSystemInternal::isPickable();
	}

	inline virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		PointsParticleSystemInternal::setDynamicShadowingEnabled(dynamicShadowing);
	}

	inline virtual float getPointSize() override {
		return PointsParticleSystemInternal::getPointSize();
	}

	inline virtual int32_t getTextureId() override {
		return PointsParticleSystemInternal::getTextureId();
	}

	inline virtual void setPickable(bool pickable) override {
		PointsParticleSystemInternal::setPickable(pickable);
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
