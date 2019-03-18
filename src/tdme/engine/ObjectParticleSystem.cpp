#include <tdme/engine/ObjectParticleSystem.h>

#include <vector>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::vector;
using std::string;

using tdme::engine::ObjectParticleSystem;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;

ObjectParticleSystem::ObjectParticleSystem(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter) :
	ObjectParticleSystemInternal(id, model, scale, autoEmit, enableDynamicShadows, maxCount, emitter)
{
}

void ObjectParticleSystem::initialize()
{
	for (auto object: objects) object->setParentEntity(this);
}

void ObjectParticleSystem::fromTransformations(const Transformations& transformations)
{
	ObjectParticleSystemInternal::fromTransformations(transformations);
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ObjectParticleSystem::update()
{
	ObjectParticleSystemInternal::update();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ObjectParticleSystem::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (this->enabled == enabled) return;
	// frustum if root entity
	if (parentEntity == nullptr) {
		// frustum culling enabled?
		if (frustumCulling == true) {
			// yeo, add or remove from partition
			if (enabled == true) {
				if (engine != nullptr) engine->partition->addEntity(this);
			} else {
				if (engine != nullptr) engine->partition->removeEntity(this);
			}
		}
	}
	// call parent class::setEnabled()
	ObjectParticleSystemInternal::setEnabled(enabled);
}

void ObjectParticleSystem::updateParticles()
{
	ObjectParticleSystemInternal::updateParticles();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

bool ObjectParticleSystem::isFrustumCulling() {
	return frustumCulling;
}

void ObjectParticleSystem::setFrustumCulling(bool frustumCulling) {
	// check if enabled and engine attached
	if (enabled == true && engine != nullptr) {
		// had frustum culling
		if (this->frustumCulling == true) {
			// yep, remove if set to false now
			if (frustumCulling == false) engine->partition->removeEntity(this);
		} else {
			// yep, add if set to true now
			if (frustumCulling == true) engine->partition->addEntity(this);
		}
	}
	this->frustumCulling = frustumCulling;
	// delegate change to engine
	if (parentEntity == nullptr && engine != nullptr) engine->updateEntity(this);
}

void ObjectParticleSystem::setAutoEmit(bool autoEmit) {
	// delegate to base class
	ObjectParticleSystemInternal::setAutoEmit(autoEmit);
	// delegate change to engine
	if (parentEntity == nullptr && engine != nullptr) engine->updateEntity(this);
}

void ObjectParticleSystem::dispose()
{
	ObjectParticleSystemInternal::dispose();
}

void ObjectParticleSystem::setEngine(Engine* engine)
{
	ObjectParticleSystemInternal::setEngine(engine);
}

void ObjectParticleSystem::setRenderer(GLRenderer* renderer)
{
	ObjectParticleSystemInternal::setRenderer(renderer);
}

