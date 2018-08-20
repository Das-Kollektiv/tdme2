#pragma once

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
#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemEntityInternal.h>
#include <tdme/engine/Entity.h>

using std::string;

using tdme::engine::subsystems::particlesystem::PointsParticleSystemEntityInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Transformations;
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
class tdme::engine::PointsParticleSystemEntity final
	: public PointsParticleSystemEntityInternal
	, public Entity
{
private:
	bool frustumCulling { true };

public:
	// overriden methods
	void initialize() override;
	BoundingBox* getBoundingBox() override;
	BoundingBox* getBoundingBoxTransformed() override;
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
	 * @param doCollisionTests do collision tests
	 * @param emitter emitter
	 * @param maxPoints max points
	 * @param autoEmit auto emit
	 */
	PointsParticleSystemEntity(const string& id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit);
public:
	// overridden methods
	virtual void setEngine(Engine* engine) override;
	virtual void setRenderer(GLRenderer* renderer) override;
	virtual void dispose() override;

	inline virtual const Color4& getEffectColorAdd() const override {
		return PointsParticleSystemEntityInternal::getEffectColorAdd();
	}

	inline virtual void setEffectColorAdd(const Color4& effectColorAdd) override {
		PointsParticleSystemEntityInternal::setEffectColorAdd(effectColorAdd);
	}

	inline virtual const Color4& getEffectColorMul() const override {
		return PointsParticleSystemEntityInternal::getEffectColorMul();
	}

	inline virtual void setEffectColorMul(const Color4& effectColorMul) override {
		PointsParticleSystemEntityInternal::setEffectColorMul(effectColorMul);
	}

	inline virtual const string& getId() override {
		return PointsParticleSystemEntityInternal::getId();
	}

	inline virtual bool isDynamicShadowingEnabled() override {
		return PointsParticleSystemEntityInternal::isDynamicShadowingEnabled();
	}

	inline virtual bool isEnabled() override {
		return PointsParticleSystemEntityInternal::isEnabled();
	}

	inline virtual bool isPickable() override {
		return PointsParticleSystemEntityInternal::isPickable();
	}

	inline virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		PointsParticleSystemEntityInternal::setDynamicShadowingEnabled(dynamicShadowing);
	}

	inline virtual void setPickable(bool pickable) override {
		PointsParticleSystemEntityInternal::setPickable(pickable);
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
