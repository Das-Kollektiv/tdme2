#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/FogParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/fwd-tdme.h>

using std::string;

using tdme::engine::Texture;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::FogParticleSystemInternal;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::ParticleSystem;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Fog particle system entity to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::FogParticleSystem final
	: public FogParticleSystemInternal
	, public ParticleSystem
{
	friend class tdme::engine::ParticleSystemGroup;

private:
	bool frustumCulling { true };

	RenderPass renderPass { RENDERPASS_STANDARD };

	// overridden methods
	inline void applyParentTransform(const Transform& parentTransform) override {
		Transform::applyParentTransform(parentTransform);
		updateInternal();
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param emitter emitter
	 * @param maxPoints max points
	 * @param pointSize point size
	 * @param texture texture
	 * @param textureHorizontalSprites texture horizonal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 * @param fps frames per seconds
	 */
	FogParticleSystem(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, Texture* texture = nullptr, int32_t textureHorizontalSprites = 1, int32_t textureVerticalSprites = 1, float fps = 10.0f);

	// overridden methods
	inline EntityType getEntityType() override {
		return ENTITYTYPE_FOGPARTICLESYSTEM;
	}
	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void initialize() override;
	void dispose() override;

	inline bool isEnabled() override {
		return FogParticleSystemInternal::isEnabled();
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
		return FogParticleSystemInternal::getEmitter();
	}

	inline const Color4& getEffectColorAdd() const override {
		return FogParticleSystemInternal::getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		FogParticleSystemInternal::setEffectColorAdd(effectColorAdd);
	}

	inline const Color4& getEffectColorMul() const override {
		return FogParticleSystemInternal::getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		FogParticleSystemInternal::setEffectColorMul(effectColorMul);
	}

	inline const string& getId() override {
		return FogParticleSystemInternal::getId();
	}

	inline bool isContributesShadows() override {
		return FogParticleSystemInternal::isContributesShadows();
	}

	inline void setContributesShadows(bool contributesShadows) override {
		FogParticleSystemInternal::setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return FogParticleSystemInternal::isReceivesShadows();
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		FogParticleSystemInternal::setReceivesShadows(receivesShadows);
	}

	inline bool isPickable() override {
		return FogParticleSystemInternal::isPickable();
	}

	inline void setPickable(bool pickable) override {
		FogParticleSystemInternal::setPickable(pickable);
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

	inline const Vector3& getPivot() const override {
		return Transform::getPivot();
	}

	inline void setPivot(const Vector3& pivot) override {
		Transform::setPivot(pivot);
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
		return Transform::getTransformMatrix();
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
		return FogParticleSystemInternal::isActive();
	}

	inline bool isAutoEmit() override {
		return FogParticleSystemInternal::isAutoEmit();
	}

	inline int emitParticles() override {
		return FogParticleSystemInternal::emitParticles();
	}

	void setAutoEmit(bool autoEmit) override;
	void updateParticles() override;

	inline const Transform& getLocalTransform() override {
		return FogParticleSystemInternal::getLocalTransform();
	}
	inline void setLocalTransform(const Transform& transform) override {
		FogParticleSystemInternal::setLocalTransform(transform);
	}
	inline Texture* getTexture() {
		return FogParticleSystemInternal::getTexture();
	}

};
