#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::string;

using tdme::engine::Texture;
using tdme::engine::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::ParticleSystem;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Point particle system entity to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::PointsParticleSystem final
	: public PointsParticleSystemInternal
	, public ParticleSystem
{
	friend class tdme::engine::ParticleSystemGroup;

private:
	bool frustumCulling { true };
	RenderPass renderPass { RENDERPASS_STANDARD };

	// overridden methods
	inline void setParentTransform(const Transform& parentTransform) override {
		PointsParticleSystemInternal::setParentTransform(parentTransform);
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(PointsParticleSystem)

	/**
	 * Public constructor
	 * @param id id
	 * @param emitter emitter
	 * @param maxPoints max points
	 * @param pointSize point size
	 * @param autoEmit auto emit
	 * @param texture texture
	 * @param textureHorizonalSprites texture horizonal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 * @param fps frames per seconds
	 */
	PointsParticleSystem(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, bool autoEmit, Texture* texture = nullptr, int32_t textureHorizontalSprites = 1, int32_t textureVerticalSprites = 1, float fps = 10.0f);

	// overridden methods
	inline EntityType getEntityType() override {
		return ENTITYTYPE_POINTSPARTICLESYSTEM;
	}
	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void initialize() override;
	void dispose() override;

	inline bool isEnabled() override {
		return PointsParticleSystemInternal::isEnabled();
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
		return PointsParticleSystemInternal::getEmitter();
	}

	inline const Color4& getEffectColorAdd() const override {
		return PointsParticleSystemInternal::getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		PointsParticleSystemInternal::setEffectColorAdd(effectColorAdd);
	}

	inline const Color4& getEffectColorMul() const override {
		return PointsParticleSystemInternal::getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		PointsParticleSystemInternal::setEffectColorMul(effectColorMul);
	}

	inline const string& getId() override {
		return PointsParticleSystemInternal::getId();
	}

	inline bool isPickable() override {
		return PointsParticleSystemInternal::isPickable();
	}

	inline void setPickable(bool pickable) override {
		PointsParticleSystemInternal::setPickable(pickable);
	}

	inline bool isContributesShadows() override {
		return PointsParticleSystemInternal::isContributesShadows();
	}

	inline void setContributesShadows(bool contributesShadows) override {
		PointsParticleSystemInternal::setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return PointsParticleSystemInternal::isReceivesShadows();
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		PointsParticleSystemInternal::setReceivesShadows(receivesShadows);
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
		return PointsParticleSystemInternal::isActive();
	}

	inline bool isAutoEmit() override {
		return PointsParticleSystemInternal::isAutoEmit();
	}

	inline int emitParticles() override {
		return PointsParticleSystemInternal::emitParticles();
	}

	void setAutoEmit(bool autoEmit) override;
	void updateParticles() override;

	inline const Transform& getLocalTransform() override {
		return PointsParticleSystemInternal::getLocalTransform();
	}
	inline void setLocalTransform(const Transform& transform) override {
		PointsParticleSystemInternal::setLocalTransform(transform);
	}
	inline Texture* getTexture() {
		return PointsParticleSystemInternal::getTexture();
	}

};
