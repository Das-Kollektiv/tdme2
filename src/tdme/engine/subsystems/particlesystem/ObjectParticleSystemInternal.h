#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectInternal;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Particle system which displays objects as particles
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::particlesystem::ObjectParticleSystemInternal
	: public Transform
	, public virtual ParticleSystemInternal
{
protected:
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	string id;
	bool enabled;
	Model* model { nullptr };
	Vector3 objectScale;
	bool autoEmit;
	bool contributesShadows;
	bool receivesShadows;
	vector<Particle> particles;
	vector<Object*> objects;
	vector<Object*> enabledObjects;
	BoundingBox boundingBox;
	BoundingBox worldBoundingBox;
	Transform inverseTransform;
	ParticleEmitter* emitter { nullptr };
	bool pickable;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	float particlesToSpawnRemainder;
	Transform localTransform;

	/**
	 * Update internal
	 */
	inline void updateInternal() {
		Vector3 scale;
		getTransformMatrix().getScale(scale);
		scale.scale(objectScale);
		scale.scale(localTransform.getScale());
		for (auto object: objects) {
			object->setScale(scale);
			object->update();
		}
		inverseTransform.setTransform(*this);
		inverseTransform.invert();
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
	 * @param maxCount maxCount
	 * @param emitter emitter
	 */
	ObjectParticleSystemInternal(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool contributesShadows, bool receivesShadows, int32_t maxCount, ParticleEmitter* emitter);

	/**
	 * Destructor
	 */
	virtual ~ObjectParticleSystemInternal();

	// overridden methods
	inline ParticleEmitter* getEmitter() override {
		return emitter;
	}

	const string& getId() override;
	void setEngine(Engine* engine);
	void setRenderer(Renderer* renderer);
	inline bool isEnabled() override {
		return enabled;
	}
	inline bool isActive() override {
		return enabledObjects.size() > 0;
	}
	inline void setEnabled(bool enabled) override {
		this->enabled = enabled;
	}
	inline const Color4& getEffectColorMul() const override {
		return effectColorMul;
	}
	inline void setEffectColorMul(const Color4& effectColorMul) override {
		this->effectColorMul = effectColorMul;
	}
	inline const Color4& getEffectColorAdd() const override {
		return effectColorAdd;
	}
	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		this->effectColorAdd = effectColorAdd;
	}
	inline bool isPickable() override {
		return pickable;
	}
	inline void setPickable(bool pickable) override {
		this->pickable = pickable;
	}
	inline bool isAutoEmit() override {
		return autoEmit;
	}
	inline void setAutoEmit(bool autoEmit) override {
		this->autoEmit = autoEmit;
	}

	/**
	 * @return if entity contributes to shadows
	 */
	inline bool isContributesShadows() {
		return contributesShadows;
	}

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	inline void setContributesShadows(bool contributesShadows) {
		this->contributesShadows = contributesShadows;
		for (auto i = 0; i < objects.size(); i++) objects[i]->setContributesShadows(contributesShadows);
	}

	/**
	 * @return if entity receives shadows
	 */
	inline bool isReceivesShadows() {
		return receivesShadows;
	}

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	inline void setReceivesShadows(bool receivesShadows) {
		this->receivesShadows = receivesShadows;
		for (auto i = 0; i < objects.size(); i++) objects[i]->setReceivesShadows(receivesShadows);
	}

	/**
	 * Update transform
	 */
	void update() override;
	void setTransform(const Transform& transform) override;
	int emitParticles() override;
	void updateParticles() override;
	void dispose();

	inline const Transform& getLocalTransform() override {
		return localTransform;
	}
	inline void setLocalTransform(const Transform& transform) override {
		this->localTransform = transform;
		updateInternal();
	}

};
