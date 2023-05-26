#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/ObjectParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ObjectParticleSystemInternal;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::ParticleSystem;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Object particle system entity to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::ObjectParticleSystem final
	: public ObjectParticleSystemInternal
	, public ParticleSystem
{
	friend class tdme::engine::ParticleSystemGroup;

private:
	bool frustumCulling { true };
	RenderPass renderPass { RENDERPASS_STANDARD };

	// overridden methods
	inline void setParentTransform(const Transform& transform) override {
		ObjectParticleSystemInternal::setParentTransform(transform);
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 * @param scale scale
	 * @param autoEmit auto emit
	 * @param contributesShadows enable contributes shadows
	 * @param receivesShadows enable receives shadows
	 * @param maxCount max count
	 * @param emitter emitter
	 */
	ObjectParticleSystem(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool contributesShadows, bool receivesShadows, int32_t maxCount, ParticleEmitter* emitter);

	// overridden method
	inline EntityType getEntityType() override {
		return ENTITYTYPE_OBJECTPARTICLESYSTEM;
	}

	/**
	 * @return objects
	 */
	inline const vector<Object*>& getObjects() {
		return objects;
	}

	/**
	 * @return enabled objects
	 */
	inline const vector<Object*>& getEnabledObjects() {
		return enabledObjects;
	}

	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void initialize() override;
	void dispose() override;

	inline bool isEnabled() override {
		return ObjectParticleSystemInternal::isEnabled();
	}

	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return &worldBoundingBox;
	}

	inline ParticleEmitter* getEmitter() override {
		return ObjectParticleSystemInternal::getEmitter();
	}

	inline const Color4& getEffectColorAdd() const override {
		return ObjectParticleSystemInternal::getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		ObjectParticleSystemInternal::setEffectColorAdd(effectColorAdd);
	}

	inline const Color4& getEffectColorMul() const override {
		return ObjectParticleSystemInternal::getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		ObjectParticleSystemInternal::setEffectColorMul(effectColorMul);
	}

	inline const string& getId() override {
		return ObjectParticleSystemInternal::getId();
	}

	inline bool isContributesShadows() override {
		return ObjectParticleSystemInternal::isContributesShadows();
	}

	inline void setContributesShadows(bool contributesShadows) override {
		ObjectParticleSystemInternal::setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return ObjectParticleSystemInternal::isReceivesShadows();
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		ObjectParticleSystemInternal::setReceivesShadows(receivesShadows);
	}

	inline bool isPickable() override {
		return ObjectParticleSystemInternal::isPickable();
	}

	inline void setPickable(bool pickable) override {
		ObjectParticleSystemInternal::setPickable(pickable);
	}

	inline const Vector3& getTranslation() const override {
		return Transform::getTranslation();
	}

	inline void setTranslation(const Vector3& translation) override {
		Transform::setTranslation(translation);
	}

	inline const Vector3& getScale() const override {
		return Transform::getScale();
	}

	inline void setScale(const Vector3& scale) override {
		Transform::setScale(scale);
	}

	inline const int getRotationCount() const override {
		return Transform::getRotationCount();
	}

	inline Rotation& getRotation(const int idx) override {
		return Transform::getRotation(idx);
	}

	inline void addRotation(const Vector3& axis, const float angle) override {
		Transform::addRotation(axis, angle);
	}

	inline void removeRotation(const int idx) override {
		Transform::removeRotation(idx);
	}

	inline const Vector3& getRotationAxis(const int idx) const override {
		return Transform::getRotationAxis(idx);
	}

	inline void setRotationAxis(const int idx, const Vector3& axis) override {
		Transform::setRotationAxis(idx, axis);
	}

	inline const float getRotationAngle(const int idx) const override {
		return Transform::getRotationAngle(idx);
	}

	inline void setRotationAngle(const int idx, const float angle) override {
		Transform::setRotationAngle(idx, angle);
	}

	inline const Quaternion& getRotationsQuaternion() const override {
		return Transform::getRotationsQuaternion();
	}

	inline const Matrix4x4& getTransformMatrix() const override {
		return entityTransformMatrix;
	}

	inline const Transform& getParentTransform() const override {
		return parentTransform;
	}

	inline const Transform& getTransform() const override {
		return *this;
	}

	void setTransform(const Transform& transform) override;

	inline RenderPass getRenderPass() const override {
		return renderPass;
	}

	inline void setRenderPass(RenderPass renderPass) override {
		this->renderPass = renderPass;
	}

	inline bool isActive() override {
		return ObjectParticleSystemInternal::isActive();
	}

	inline bool isAutoEmit() override {
		return ObjectParticleSystemInternal::isAutoEmit();
	}

	inline int emitParticles() override {
		return ObjectParticleSystemInternal::emitParticles();
	}

	void setAutoEmit(bool autoEmit) override;
	void updateParticles() override;

	inline const Transform& getLocalTransform() override {
		return ObjectParticleSystemInternal::getLocalTransform();
	}
	inline void setLocalTransform(const Transform& transform) override {
		ObjectParticleSystemInternal::setLocalTransform(transform);
	}

};
