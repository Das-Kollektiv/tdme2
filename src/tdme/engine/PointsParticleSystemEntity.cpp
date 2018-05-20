#include <tdme/engine/PointsParticleSystemEntity.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::string;

using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;

PointsParticleSystemEntity::PointsParticleSystemEntity(const string& id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit) :
	PointsParticleSystemEntityInternal(id, doCollisionTests, emitter, maxPoints, autoEmit)
{
}

void PointsParticleSystemEntity::initialize()
{
}

BoundingBox* PointsParticleSystemEntity::getBoundingBox()
{
	return boundingBox;
}

BoundingBox* PointsParticleSystemEntity::getBoundingBoxTransformed()
{
	return boundingBoxTransformed;
}

void PointsParticleSystemEntity::fromTransformations(const Transformations& transformations)
{
	PointsParticleSystemEntityInternal::fromTransformations(transformations);
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void PointsParticleSystemEntity::update()
{
	PointsParticleSystemEntityInternal::update();
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void PointsParticleSystemEntity::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (this->enabled == enabled) return;
	// frustum culling enabled?
	if (frustumCulling == true) {
		// yeo, add or remove from partition
		if (enabled == true) {
			if (engine != nullptr) engine->partition->addEntity(this);
		} else {
			if (engine != nullptr) engine->partition->removeEntity(this);
		}
	}
	// call parent class::setEnabled()
	PointsParticleSystemEntityInternal::setEnabled(enabled);
}

void PointsParticleSystemEntity::updateParticles()
{
	PointsParticleSystemEntityInternal::updateParticles();
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

bool PointsParticleSystemEntity::isFrustumCulling() {
	return frustumCulling;
}

void PointsParticleSystemEntity::setFrustumCulling(bool frustumCulling) {
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
	if (engine != nullptr) engine->updateEntity(this);
}

void PointsParticleSystemEntity::setAutoEmit(bool autoEmit) {
	// delegate to base class
	PointsParticleSystemEntityInternal::setAutoEmit(autoEmit);
	// delegate change to engine
	if (engine != nullptr) engine->updateEntity(this);
}

void PointsParticleSystemEntity::dispose()
{
	PointsParticleSystemEntityInternal::dispose();
}

void PointsParticleSystemEntity::setEngine(Engine* engine)
{
	PointsParticleSystemEntityInternal::setEngine(engine);
}

void PointsParticleSystemEntity::setRenderer(GLRenderer* renderer)
{
	PointsParticleSystemEntityInternal::setRenderer(renderer);
}

