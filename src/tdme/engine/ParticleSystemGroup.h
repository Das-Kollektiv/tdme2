#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::ParticleSystem;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Particle system group, which combines several particle systems into a group, to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::ParticleSystemGroup final
	: public Transform
	, public ParticleSystem
{
private:
	Engine* engine { nullptr };
	bool frustumCulling { true };
	RenderPass renderPass { RENDERPASS_STANDARD };

	string id;
	bool contributesShadows;
	bool receivesShadows;
	bool enabled;
	bool pickable;
	bool autoEmit;
	BoundingBox boundingBox;
	BoundingBox boundingBoxTransformed;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	vector<ParticleSystem*> particleSystems;
	Transform localTransform;

	// overridden methods
	inline void applyParentTransform(const Transform& parentTransform) override {
		Transform::applyParentTransform(parentTransform);
		for (auto particleSystem: particleSystems) particleSystem->applyParentTransform(parentTransform);
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param autoEmit auto emit
	 * @param contributesShadows contributes shadows
	 * @param receivesShadows receives shadows
	 * @param particleSystems particle systems
	 */
	ParticleSystemGroup(const string& id, bool autoEmit, bool contributesShadows, bool receivesShadows, const vector<ParticleSystem*>& particleSystems);

	/**
	 * Destructor
	 */
	~ParticleSystemGroup();

	// overridden method
	inline EntityType getEntityType() override {
		return ENTITYTYPE_PARTICLESYSTEMGROUP;
	}

	/**
	 * @return particle systems
	 */
	inline const vector<ParticleSystem*>& getParticleSystems() {
		return particleSystems;
	}

	// overridden methods
	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void initialize() override;
	void dispose() override;

	inline bool isEnabled() override {
		return enabled;
	}

	void setEnabled(bool enabled) override;

	inline bool isFrustumCulling() override {
		return frustumCulling;
	}

	void setFrustumCulling(bool frustumCulling) override;
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		if (particleSystems.empty() == false) {
			// compute new bounding box
			boundingBox.fromBoundingVolume(dynamic_cast<Entity*>(particleSystems[0])->getBoundingBox());
			for (auto i = 1; i < particleSystems.size(); i++) {
				boundingBox.extend(dynamic_cast<Entity*>(particleSystems[i])->getBoundingBox());
			}
			boundingBox.update();

			// update bounding box transformed
			boundingBoxTransformed.fromBoundingVolumeWithTransform(&boundingBox, *this);
		}

		//
		return &boundingBox;
	}

	inline BoundingBox* getBoundingBoxTransformed() override {
		if (particleSystems.empty() == false) {
			// compute new bounding box
			boundingBox.fromBoundingVolume(dynamic_cast<Entity*>(particleSystems[0])->getBoundingBox());
			for (auto i = 1; i < particleSystems.size(); i++) {
				boundingBox.extend(dynamic_cast<Entity*>(particleSystems[i])->getBoundingBox());
			}
			boundingBox.update();

			// update bounding box transformed
			boundingBoxTransformed.fromBoundingVolumeWithTransform(&boundingBox, *this);
		}

		//
		return &boundingBoxTransformed;
	}

	inline ParticleEmitter* getEmitter() override {
		return nullptr;
	}

	inline const Color4& getEffectColorAdd() const override {
		return effectColorAdd;
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		for (auto particleSystem: particleSystems) particleSystem->setEffectColorAdd(effectColorAdd);
		this->effectColorAdd = effectColorAdd;
	}

	inline const Color4& getEffectColorMul() const override {
		return effectColorMul;
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		for (auto particleSystem: particleSystems) particleSystem->setEffectColorMul(effectColorMul);
		this->effectColorMul = effectColorMul;
	}

	inline const string& getId() override {
		return id;
	}

	inline bool isContributesShadows() override {
		return contributesShadows;
	}

	inline void setContributesShadows(bool contributesShadows) override {
		this->contributesShadows = contributesShadows;
		for (auto particleSystem: particleSystems) {
			auto ops = dynamic_cast<ObjectParticleSystem*>(particleSystem);
			if (ops != nullptr) ops->setContributesShadows(contributesShadows);
		}
	}

	inline bool isReceivesShadows() override {
		return receivesShadows;
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		this->receivesShadows = receivesShadows;
		for (auto particleSystem: particleSystems) {
			auto ops = dynamic_cast<ObjectParticleSystem*>(particleSystem);
			if (ops != nullptr) ops->setReceivesShadows(receivesShadows);
		}
	}

	inline bool isPickable() override {
		return pickable;
	}

	inline void setPickable(bool pickable) override {
		this->pickable = true;
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
		for (auto particleSystem: particleSystems) {
			if (particleSystem->isActive() == true) return true;
		}
		return false;
	}

	inline bool isAutoEmit() override {
		return autoEmit;
	}

	inline int emitParticles() override {
		auto emittedParticles = 0;
		for (auto particleSystem: particleSystems) emittedParticles+= particleSystem->emitParticles();
		return emittedParticles;
	}

	void setAutoEmit(bool autoEmit) override;
	void updateParticles() override;

	inline const Transform& getLocalTransform() override {
		return localTransform;
	}

	inline void setLocalTransform(const Transform& transform) override {
		localTransform = transform;
		for (auto particleSystem: particleSystems) particleSystem->setLocalTransform(localTransform);
	}

};
