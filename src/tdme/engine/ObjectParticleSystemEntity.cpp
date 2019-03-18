#include <tdme/engine/ObjectParticleSystemEntity.h>

#include <vector>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::vector;
using std::string;

using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;

ObjectParticleSystemEntity::ObjectParticleSystemEntity(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter) :
	ObjectParticleSystemEntityInternal(id, model, scale, autoEmit, enableDynamicShadows, maxCount, emitter)
{
}

void ObjectParticleSystemEntity::initialize()
{
	for (auto object: objects) object->setParentEntity(this);
}

void ObjectParticleSystemEntity::fromTransformations(const Transformations& transformations)
{
	ObjectParticleSystemEntityInternal::fromTransformations(transformations);
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ObjectParticleSystemEntity::update()
{
	ObjectParticleSystemEntityInternal::update();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ObjectParticleSystemEntity::setEnabled(bool enabled)
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
	ObjectParticleSystemEntityInternal::setEnabled(enabled);
}

void ObjectParticleSystemEntity::updateParticles()
{
	ObjectParticleSystemEntityInternal::updateParticles();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

bool ObjectParticleSystemEntity::isFrustumCulling() {
	return frustumCulling;
}

void ObjectParticleSystemEntity::setFrustumCulling(bool frustumCulling) {
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

void ObjectParticleSystemEntity::setAutoEmit(bool autoEmit) {
	// delegate to base class
	ObjectParticleSystemEntityInternal::setAutoEmit(autoEmit);
	// delegate change to engine
	if (parentEntity == nullptr && engine != nullptr) engine->updateEntity(this);
}

void ObjectParticleSystemEntity::dispose()
{
	ObjectParticleSystemEntityInternal::dispose();
}

void ObjectParticleSystemEntity::setEngine(Engine* engine)
{
	ObjectParticleSystemEntityInternal::setEngine(engine);
}

void ObjectParticleSystemEntity::setRenderer(GLRenderer* renderer)
{
	ObjectParticleSystemEntityInternal::setRenderer(renderer);
}

